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


using namespace std;
using namespace boost::filesystem;




int main(int ac, char* av[])
{

    mw::ImageFinderOptions po(ac, av);

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
         in_dir = path{current_path()};
    }

    if (out_csv.empty()) {
         out_csv = path{in_dir / path("found_files.csv")};
    }

    cout << "In-dir: " << in_dir << endl;
    cout << "out_csv: " << out_csv << endl;
    mw::print_iterable(file_types);


    vector<path> all_paths = mw::fs::get_all_paths(in_dir);

    cout << all_paths.size() << endl;


    return 0;
}
