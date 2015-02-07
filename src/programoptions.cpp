#include "programoptions.h"
#include "utils.h"

#include <iostream>
#include <memory>

namespace mw {

    using namespace std;

    ProgramOptions::ProgramOptions(int acc, char *avv[]):
        ac {acc}, av {avv}
    {

        po = make_unique<options_description>(ABOUT);
        p  = make_unique<positional_options_description>();

        add_options();
    }


    void ProgramOptions::add_options()
    {
        po->add_options()
            ("help,h", "produce help message")
            ("in-dir,I",  value<string>(), "input folder")
            ("out-dir,O", value<string>(), "output folder")
            ("file-type,T", value<string>(),
                            "file type to search, e.g. \"DMC,TIFF,JPEG\"")
            ("verbose,v", value<bool>()->implicit_value(true),
                            "verbose output")
            ("path-file,p", value<string>(),
                            "files to store image paths found")
            ("csv-file,C", value<string>(),
                          "output csv file path");

        p->add("in-dir", -1);
    }




    bool ProgramOptions::parse_options() {

     try
     {
         store(command_line_parser(ac,av)
                  .options(*po).positional(*p).run(), vm);

         notify(vm);
     } catch  (const error & e) {
         mw::errp(e.what());
         print(cout);
         return false;
     }
    return true;

    }

    void ProgramOptions::print(ostream & os)
    {
        po->print(os);
    }


    ProgramOptions::~ProgramOptions()
    {

    }

}

