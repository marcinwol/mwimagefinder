#ifndef IMAGEFINDEROPTIONS_H
#define IMAGEFINDEROPTIONS_H

#include "programoptions.h"
#

namespace mw {

    using namespace std;

    class ImageFinderOptions: public ProgramOptions
    {
    public:

        enum class IMG_SIZE_CMP {GL, LO, LE, GT, GE, NONE};

        ImageFinderOptions(int acc, char *avv[]);
        virtual ~ImageFinderOptions();

        size_t idx {0};

        string matched_size {};

        pair<IMG_SIZE_CMP,vector<double>>
        get_file_size_option()
        {
            string file_size = get<string>("file-size");

            IMG_SIZE_CMP size_cmp {IMG_SIZE_CMP::NONE};

            vector<double> found_size {};

            if  ((idx = file_size.find("<>")) != string::npos)
            {

              string sizes[2];
              sizes[0] = file_size.substr(0, idx);
              sizes[1] = file_size.substr(idx+2,file_size.length());

        //      cout << "found <>" <<" at "<< idx << endl;
           //   cout << sizes[0] << " " << sizes[1] << endl;

             size_cmp = IMG_SIZE_CMP::GL;

             found_size.push_back(boost::lexical_cast<double>(sizes[0]));
             found_size.push_back(boost::lexical_cast<double>(sizes[1]));

            }
            else  if (file_size.find("<=") != string::npos)
            {
             //   cout << "found <=" << endl;
                size_cmp = IMG_SIZE_CMP::LE;
                found_size.push_back(boost::lexical_cast<double>(file_size));
            }
            else if (file_size.find(">=") != string::npos)
            {
             //   cout << "found <=" << endl;
                 size_cmp = IMG_SIZE_CMP::GE;
                 found_size.push_back(boost::lexical_cast<double>(file_size));
            }
            else if (file_size.find("<") != string::npos)
            {
            //    cout << "found <" << endl;
                   size_cmp = IMG_SIZE_CMP::LE;
                   found_size.push_back(boost::lexical_cast<double>(file_size));
            }
            else if (file_size.find(">") != string::npos)
            {
           //     cout << "found >" << endl;
                size_cmp = IMG_SIZE_CMP::GT;
                found_size.push_back(boost::lexical_cast<double>(file_size));
            }

            matched_size = mw::extract_first_number(file_size);

            return pair<IMG_SIZE_CMP,vector<double>>(size_cmp, found_size);

        }

    protected:
      virtual void add_options();
      virtual void add_description();
    };



}

#endif // IMAGEFINDEROPTIONS_H
