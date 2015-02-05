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


#include "infix_iterator.h"


using namespace std;

int main(int ac, char* av[])
{

    unique_ptr<int> ip = make_unique<int>(3);


    cout << "testigng: "<< *ip << endl;
    return 0;
}
