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
    mw::print_iterable(file_types);


    vector<path> all_paths = mw::fs::get_all_paths(in_dir, true);

    cout << all_paths.size() << endl;

//    mw::MwPath img_path {"/media/sf_D_DRIVE/dcm_for_tests/ding/b/ID 12R/DICOM/S00001/SER00001/I00002"};
//    path img_path1 {"/media/sf_D_DRIVE/dcm_for_tests/ding/b/ID 12R/DICOM/S00001/SER00001/I00002"};
//    string img_path2 {"/home/m/Downloads/Julia"};


//    mw::MwImage img {img_path2};


//    cout << img.magick() << endl;
//    cout << img.getType() << endl;
//    cout << img << endl;

//    img.readProperties();

//   cout << img.getResolution() << endl;

//    for(const auto & p: img.getProperties())
//    {
//     cout << p.first <<  ": " << p.second << endl;
//    }


    return 0;
}
