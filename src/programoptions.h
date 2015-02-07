#ifndef MWPROGRAMOPTIONS_H
#define MWPROGRAMOPTIONS_H

#include <memory>

#include <boost/program_options.hpp>


namespace mw {

    using namespace std;
    using namespace boost::program_options;

    static const string ABOUT =
            "mwoimagefinder -I /input/folder \n"
            "\n"
            "The program searches an input folder (--in-dir or -I) "
            "for all images contained in it and its subfolders."
            "Once found, it generates an csv in the --in-dir folder"
            "or in the current working directory."
            "\n";

    class ProgramOptions
    {

     int ac;
     char** av;
     unique_ptr<options_description> po;
     unique_ptr<positional_options_description> p;

     variables_map vm;

    public:
      ProgramOptions() = delete;
      ProgramOptions(int acc, char *avv[]);            

      bool parse_options();
      void print(ostream & os);

      template<typename T>
      T get(const string & op_name)
      {
          T op_value {};
          if (!vm.count(op_name)) {
              return op_value;
          }

          return vm[op_name].as<T>();
      }

      virtual ~ProgramOptions();

    private:
      void add_options();


    };

}

#endif // MWPROGRAMOPTIONS_H
