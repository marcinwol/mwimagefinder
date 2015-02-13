#ifndef IMAGE_H
#define IMAGE_H


#include <iostream>

#include <Magick++.h>
#include <boost/filesystem.hpp>

#include "mwpath.h"


namespace mw {

  using namespace boost::filesystem;


  class MwImage: public Magick::Image
  {

   using Magick::Image::Image;


  public:

    MwImage(const MwPath & i_path);
    MwImage(const path & i_path);
    MwImage(const string & i_path);
    MwPath getPath() const {return img_path;}
    string getType() const;
    double getDiskSize() const;
    virtual ~MwImage();


  protected:

    MwPath img_path;
    friend ostream & operator<<(ostream & os, const MwImage & img);



  };

}


#endif // IMAGE_H
