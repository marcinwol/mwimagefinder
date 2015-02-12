#ifndef IMAGE_H
#define IMAGE_H


#include <Magick++.h>
#include <boost/filesystem.hpp>

#include "path.h"


namespace mw {

  using namespace boost::filesystem;


  class Image: public Magick::Image
  {

   using Magick::Image::Image;

  protected:
    mw::Path img_path;


  public:

    Image(const mw::Path & i_path);
    Image(const path & i_path);
    Image(const string & i_path);
    mw::Path getPath() const {return img_path;}

    virtual ~Image();
  };

}


#endif // IMAGE_H
