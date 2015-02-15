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


    vector<path> all_paths = mw::fs::get_all_paths(in_dir, true);

    vector<mw::MwPath> img_paths;


    // check if found files are images, i.e. if they
    // are recognized by ImageMagick++. If yes,
    // then save their paths.
    for (size_t i = 0; i < all_paths.size(); ++i )
    {
      const path & t = all_paths[i];
      cout << i+1 << "/"<< all_paths.size() << ": Analyzing ";
      cout << t.filename() << endl;

      if (mw::MwImage::is_image(t))  {
          //cout << "is image" << endl;
          img_paths.emplace_back(t);
      }
    }

    cout << endl
         <<"Found " << img_paths.size()
         << " out of " << all_paths.size()
         << "analyzed." << endl;



    return 0;
}
