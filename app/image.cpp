#include "image.h"

namespace mw {

  Image::Image(const mw::Path &i_path):Magick::Image(i_path.string())
  {
    img_path = i_path;
  }

  Image::Image(const path &i_path):Magick::Image(i_path.string())
  {
    img_path = mw::Path(i_path);
  }


  Image::Image(const string &i_path):Magick::Image(i_path)
  {
    img_path = mw::Path(i_path);
  }

  Image::~Image()
  {

  }

}

