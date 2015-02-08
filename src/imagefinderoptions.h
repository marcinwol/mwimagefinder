#ifndef IMAGEFINDEROPTIONS_H
#define IMAGEFINDEROPTIONS_H

#include "programoptions.h"


namespace mw {

    class ImageFinderOptions: public ProgramOptions
    {
    public:
        ImageFinderOptions(int acc, char *avv[]);
        virtual ~ImageFinderOptions();

    protected:
      virtual void add_options();
      virtual void add_description();
    };



}

#endif // IMAGEFINDEROPTIONS_H
