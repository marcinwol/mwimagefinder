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
#include <boost/format.hpp>


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
         in_dir = path {current_path()};
    }

    if (out_csv.empty()) {
         out_csv = path {in_dir / path("found_files.csv")};
    }



    cout << "In-dir: " << in_dir << endl;
    cout << "out_csv: " << out_csv << endl;

    //string p {"/media/sf_D_DRIVE/dcm_for_tests/ding/b/13.01-17.01.11/DICOM/PA000001/ST000001/SE000001/IM000001"};

    vector<path> all_paths = mw::fs::get_all_paths(in_dir, true);



    vector<mw::MwImage::uptr> vec_imgs;


    mw::mwcsv f {};

    return 0;


    // check if found files are images, i.e. if they
    // are recognized by ImageMagick++. If yes,
    // then save their paths.
    for (size_t i = 0; i < all_paths.size(); ++i )
    {
      const path & t = all_paths[i];
      cout << i+1 << "/"<< all_paths.size() << ": Analyzing ";
      cout << t.filename() << endl;

      mw::MwImage::uptr img_ptr = make_unique<mw::MwImage>();

      if (mw::MwImage::is_image(t, img_ptr))  {
          cout << "is image "
               << " :" << img_ptr->magick()
               << img_ptr->getPath()
               << endl;
          vec_imgs.push_back(move(img_ptr));

      }
    }

    cout << endl
         <<"Found " << vec_imgs.size()
         << " out of " << all_paths.size()
         << " analyzed." << endl;

    for (size_t i = 0; i < vec_imgs.size(); ++i)
    {
      const mw::MwImage::uptr & img_ptr = vec_imgs[i];
      img_ptr->readProperties();

      cout << i+1 << "/"<< all_paths.size() << ": Image found ";     

      cout << img_ptr->getPath()
           << " "
           << img_ptr->getType()
           << "res:" << img_ptr->getResolution()
           << endl;

    }



    return 0;
}
