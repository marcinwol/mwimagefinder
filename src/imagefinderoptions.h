#ifndef IMAGEFINDEROPTIONS_H
#define IMAGEFINDEROPTIONS_H

#include "programoptions.h"
#

namespace mw {

    using namespace std;

    class ImageFinderOptions: public ProgramOptions
    {
    public:

        enum class IMG_SIZE_CMP {GL, LO, GT, NONE};

        using size_opt =  pair<IMG_SIZE_CMP,vector<double>>;


        ImageFinderOptions(int acc, char *avv[]);
        virtual ~ImageFinderOptions();



        size_opt   get_file_size_option()
        {

            IMG_SIZE_CMP size_cmp {IMG_SIZE_CMP::NONE};
            vector<double> found_size {};


            string file_size = get<string>("file-size");

            if (file_size.empty())
            {
               return make_pair(size_cmp, found_size);
            }

            size_t idx {0};

            if  ((idx = file_size.find("-")) != 0 && idx != string::npos)
            {

              string sizes[2];
              sizes[0] = file_size.substr(0, idx);
              sizes[1] = file_size.substr(idx+1, file_size.length());

            // cout << "found <>" <<" at "<< idx << endl;
          //   cout << sizes[0] << " " << sizes[1] << endl;

             size_cmp = IMG_SIZE_CMP::GL;


             string size1 = mw::extract_first_number(sizes[0]);
             string size2 = mw::extract_first_number(sizes[1]);

             found_size.push_back(boost::lexical_cast<double>(size1));
             found_size.push_back(boost::lexical_cast<double>(size2));

            }
            else
            {
                string size_str = mw::extract_first_number(file_size);

                double size_dbl = boost::lexical_cast<double>(size_str);

                //  cout << size_dbl << endl;

                if  (size_dbl < 0)
                {
                     size_cmp = IMG_SIZE_CMP::LO;
                     size_dbl = - size_dbl;
                }
                else
                {
              //      cout << "GT optin" << endl;
                  size_cmp = IMG_SIZE_CMP::GT;
                }

                found_size.push_back(size_dbl);

            }


            return  make_pair(size_cmp, found_size);

        }

    protected:
      virtual void add_options();
      virtual void add_description();
    };



}

#endif // IMAGEFINDEROPTIONS_H
