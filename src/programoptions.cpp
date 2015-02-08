#include "programoptions.h"
#include "utils.h"

#include <iostream>
#include <memory>

namespace mw {

    using namespace std;

    ProgramOptions::ProgramOptions(int acc, char *avv[]):
        ac {acc}, av {avv}
    {

    }


    template<typename T>
    T ProgramOptions::get(const string & op_name)
    {
        T op_value {};
        if (!vm.count(op_name)) {
            return op_value;
        }

        return vm[op_name].as<T>();
    }

    // explisit instantiations of get template function
    template string ProgramOptions::get<string>(const string &);
    template bool ProgramOptions::get<bool>(const string &);
    template int ProgramOptions::get<int>(const string &);



    bool ProgramOptions::parse_options() {

     try
     {
         store(command_line_parser(ac,av)
                  .options(*po).positional(*p).run(), vm);

         notify(vm);

         if (get<bool>("help")) {
             show_help();
             return false;
         }

     } catch  (const error & e) {
         mw::errp(e.what());
         print(cout);
         return false;
     }
    return true;

    }

    void ProgramOptions::show_help()
    {
        cout << prog_desciption << endl;
        cout << *po << endl;
    }

    void ProgramOptions::print(ostream & os)
    {
        po->print(os);
    }


    ProgramOptions::~ProgramOptions()
    {

    }

}

