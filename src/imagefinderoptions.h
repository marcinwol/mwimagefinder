#ifndef IMAGEFINDEROPTIONS_H
#define IMAGEFINDEROPTIONS_H

#include "programoptions.h"
#

namespace mw {

    using namespace std;

    class ImageFinderOptions: public ProgramOptions
    {
    public:

        enum class IMG_SIZE_CMP {LO, LE, GT, GE};

        ImageFinderOptions(int acc, char *avv[]);
        virtual ~ImageFinderOptions();

        string get_file_size_option()
        {
            string file_size = get<string>("file-size");

            if (file_size.find("<=") != string::npos)
            {
                cout << "found <=" << endl;
            }
            else if (file_size.find(">=") != string::npos)
            {
                cout << "found <=" << endl;
            }
            else if (file_size.find("<") != string::npos)
            {
                cout << "found <" << endl;
            }else if (file_size.find(">") != string::npos)
            {
                cout << "found >" << endl;
            }

            string matched_size = mw::extract_first_number(file_size);

            cout << matched_size << endl;

            return file_size;

        }

    protected:
      virtual void add_options();
      virtual void add_description();
    };



}

#endif // IMAGEFINDEROPTIONS_H
