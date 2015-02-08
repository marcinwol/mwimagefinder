#include "imagefinderoptions.h"




namespace mw {

    using namespace std;

    ImageFinderOptions::ImageFinderOptions(
            int acc, char *avv[]): ProgramOptions(acc, avv)
    {
        add_description();

        po = make_unique<options_description>(prog_desciption);
        p  = make_unique<positional_options_description>();

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
            "\n";

    }

     void ImageFinderOptions::add_options()
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

    ImageFinderOptions::~ImageFinderOptions()
    {

    }

}

