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
#include "programoptions.h"


using namespace std;





int main(int ac, char* av[])
{

    mw::ProgramOptions progOptions(ac, av);

    if (!progOptions.parse_options()) {
        return 1;
    }

    string IN_DIR = progOptions.get<string>("in-dir");

    cout << "In-dir: " <<IN_DIR << endl;


    return 0;
}
