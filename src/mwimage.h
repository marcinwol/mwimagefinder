#ifndef IMAGE_H
#define IMAGE_H


#include <iostream>
#include <map>

#include <Magick++.h>
#include <boost/filesystem.hpp>

#include "mwpath.h"
#include "utils.h"

namespace mw {

  using namespace boost::filesystem;


  class MwImage: public Magick::Image
  {

   using Magick::Image::Image;


  public:

    typedef std::map<string, string> properties_map;


    MwImage(const MwPath & i_path);
    MwImage(const path & i_path);
    MwImage(const string & i_path);

    MwPath getPath() const {return img_path;}

    string getType() const;

    double getDiskSize() const;

    /**
     * Read image properties similar to what identify gives.
     * @brief readProperties
     */
    void readProperties();

    bool propertiesEmpty() const;

    properties_map getProperties() const;


    virtual ~MwImage();


  protected:

    MwPath img_path {};
    friend ostream & operator<<(ostream & os, const MwImage & img);

    properties_map properties {};

  };

}


#endif // IMAGE_H
