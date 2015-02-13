#include "mwimage.h"



namespace mw {

  MwImage::MwImage(const MwPath &i_path):Magick::Image(i_path.string())
  {
    img_path = i_path;
  }

  MwImage::MwImage(const path &i_path):Magick::Image(i_path.string())
  {
    img_path = MwPath(i_path);
  }


  MwImage::MwImage(const string &i_path):Magick::Image(i_path)
  {
    img_path = MwPath(i_path);
  }

  string MwImage::getType() const
  {
    return string(this->magick());
  }


  double MwImage::getDiskSize() const
  {
    return 0.0;//mw::fs::get_file_size(getPath());
  }


  MwImage::~MwImage()
  {

  }

  ostream& operator<<(ostream& os, const MwImage & img)
  {
    os << img.getPath() <<": " << img.getType() ;
    return os;
  }

}

