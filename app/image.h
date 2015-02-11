#ifndef IMAGE_H
#define IMAGE_H

#include <Magick++.h>

namespace mw {
  class Image: public Magick::Image
  {

   using Magick::Image::Image;


  public:
    Image();
    ~Image();
  };

}


#endif // IMAGE_H
