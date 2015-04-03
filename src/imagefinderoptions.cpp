#include "imagefinderoptions.h"




namespace mw {

    using namespace std;

    ImageFinderOptions::ImageFinderOptions(
            int acc, char *avv[]): ProgramOptions(acc, avv)
    {
        add_description();

        //po = make_unique<options_description>(prog_desciption);
        po =  unique_ptr<options_description>(
                    new options_description {prog_desciption}
              );
        //p  = make_unique<positional_options_description>();
        p  = unique_ptr<positional_options_description>(
                    new positional_options_description {}
             );

        add_options();
    }

    void ImageFinderOptions::add_description()
    {
       prog_desciption =
            "mwoimagefinder -I /input/folder \n"
            "\n"
            "The program searches an input folder (--in-dir or -I) "
            "for all images contained in it and its subfolders."
            "Once found, it generates an csv in the --in-dir folder"
            "or in the current working directory."
            "\nExamples:\n "
            "\n  mwimagefinder --file-type JPEG --csv-file  /tmp/found_JPEG.csv"
            "\n  mwimagefinder /tmp/ -T JPEG,DCM --csv-file  /tmp/found_JPEG.csv"
            "\n  mwimagefinder /tmp/ -T JPEG,DCM -v -f"
            "\n  mwimagefinder /tmp/ -T JPEG,DCM -v -f -s 5"
            "\n  mwimagefinder /tmp/ -T JPEG,DCM,TIFF -v -f -d -s 2-5"
            "\n";

    }

    void ImageFinderOptions::add_options()
    {
        po->add_options()
            ("help,h", value<bool>()->implicit_value(true),
                      "produce help message")
            ("in-dir,I",  value<vector<string>>()->multitoken(), "input folder")
            ("out-dir,O", value<string>(), "Location where the found images will be copied")
            ("file-type,T", value<string>(),
                            "file type to search, e.g. \"DMC,TIFF,JPEG\"")
            ("verbose,v", bool_switch()->default_value(false),
                            "verbose output")
            ("max-level,l", value<int>()->default_value(-1),
                                "max level of input folder scan (set to 1 for not going into sub-folders")
            ("fast,f", bool_switch()->default_value(false),
                                "fast scan using only file signature. Dont use imagemagick")
            ("detailed,d", bool_switch()->default_value(false),
                                    "put all properties of images found into the csv files")
            ("path-file,p", value<string>(),
                            "files to store image paths found")
            ("file-size,s", value<string>(),
                                "Limit search to files of given size [MB], e.g.: 1 or -5")          
            ("csv-file,C", value<string>(),
                          "output csv file path");

        p->add("in-dir", -1);
    }

    ImageFinderOptions::~ImageFinderOptions()
    {

    }

}

