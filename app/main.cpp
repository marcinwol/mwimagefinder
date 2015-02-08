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





int main(int ac, char* av[])
{

    mw::ImageFinderOptions po(ac, av);

    if (!po.parse_options()) {
        return 1;
    }

    string in_dir    = po.get<string>("in-dir");
    string out_dir   = po.get<string>("out-dir");
    string file_type = po.get<string>("file-type");
    string path_file = po.get<string>("path-file");
    string out_csv   = po.get<string>("csv-file");
    bool verbose     = po.get<bool>("verbose");


    cout << "In-dir: " << in_dir << endl;


    return 0;
}
