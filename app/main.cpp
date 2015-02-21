#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <array>
#include <map>
#include <memory>
#include <tuple>

#include <stdlib.h>


#include <Magick++.h>
#include <magick/MagickCore.h>

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>


#include "../ext/format.h"

#include "utils.h"
#include "imagefinderoptions.h"
#include "mwimage.h"
#include "mwpath.h"
#include "csv/mwcsv.h"



using namespace std;
using namespace boost::filesystem;




int main(int ac, char* av[])
{

    mw::ImageFinderOptions po {ac, av};

    if (!po.parse_options()) {
        return 1;
    }

    bool verbose        {po.get<bool>("verbose")};
    path in_dir         {po.get<string>("in-dir")};
    path out_dir        {po.get<string>("out-dir")};
    path path_file      {po.get<string>("path-file")};
    path out_csv        {po.get<string>("csv-file")};
    string file_type    {po.get<string>("file-type")};

    vector<string> file_types {mw::split(file_type, ',')};

    if (!exists(in_dir)) {
         in_dir = current_path();
    }

    if (out_csv.empty()) {
         out_csv = path {current_path() / path("found_files.csv")};
    }


    cout << "In-dir: " << in_dir << endl;
    cout << "out_csv: " << out_csv << endl;


    vector<path> all_paths = mw::fs::get_all_paths(in_dir, true);

    vector<mw::MwImage::uptr> vec_imgs;




    // check if found files are images, i.e. if they
    // are recognized by ImageMagick++. If yes,
    // then save their paths.
    for (size_t i = 0; i < all_paths.size(); ++i )
    {
      const path & t = all_paths[i];

      fmt::print("{}/{}: Analyzing {}...", i+1, all_paths.size(), t.filename());

      mw::MwImage::uptr img_ptr = make_unique<mw::MwImage>();

      if (mw::MwImage::is_image(t, img_ptr))  {
          fmt::print(" is image: {}.\n",  img_ptr->magick());
          vec_imgs.push_back(move(img_ptr));
      } else {
          fmt::print(" not an image.\n",  img_ptr->magick());
      }
    }



    if (vec_imgs.empty())
    {
        mw::errp("\nNo image files found!.\n");
        return 0;
    }


    fmt::print("Found {} images out of {} analyzed\n",
               vec_imgs.size(), all_paths.size());


    // save results to the output csv file
    ofstream of {out_csv.string()};
    if (!of)
    {
      mw::errp(out_csv.string() + " creation failed!");
    }

    mw::mwcsv_writer f {of};

    string header[] = {"File", "Type", "Size[MB]",
                       "ps_x[mm]", "ps_y[mm]",
                       "DPIx", "DPIy"};
    f.write(header);

    vector<string> a_line {7};

    for (size_t i = 0; i < vec_imgs.size(); ++i)
    {
      const mw::MwImage::uptr & img_ptr = vec_imgs[i];
      img_ptr->readProperties();

      const mw::MwResolution & res = img_ptr->getResolution();

      fmt::print("Image {}/{}:", i+1, all_paths.size(), img_ptr->getPath());

      a_line[0] = "\""+img_ptr->getPath().string()+"\"";
      a_line[1] = img_ptr->getType();
      a_line[2] = to_string(img_ptr->getDiskSize());
      a_line[3] = to_string(res.getPS()[0]);
      a_line[4] = to_string(res.getPS()[1]);
      a_line[5] = to_string(res.getDPI()[0]);
      a_line[6] = to_string(res.getDPI()[1]);

      fmt::print("{}\n", mw::join(a_line));


      f.write(a_line);

    }

    cout << "\nCSV file saved: " << out_csv << endl;


    cout << endl;
    return 0;
}
