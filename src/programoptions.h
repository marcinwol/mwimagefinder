#ifndef MWPROGRAMOPTIONS_H
#define MWPROGRAMOPTIONS_H

#include <memory>

#include <boost/program_options.hpp>
#include <boost/regex.hpp>

#include "utils.h"

namespace mw {

    using namespace std;
    using namespace boost::program_options;

    class ProgramOptions
    {

    protected:
     int ac;
     char** av;

     string prog_desciption;

     unique_ptr<options_description> po;
     unique_ptr<positional_options_description> p;

     variables_map vm;

    public:
      ProgramOptions() = delete;
      ProgramOptions(int acc, char *avv[]);            

      bool parse_options();
      void print(ostream & os);

      template<typename T>
      T get(const string & op_name);

      virtual ~ProgramOptions();

      variables_map get_vm() const {return vm;}

    protected:
      virtual void show_help();
      virtual void add_options() = 0;
      virtual void add_description() = 0;


    };

}

#endif // MWPROGRAMOPTIONS_H
