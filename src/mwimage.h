#ifndef IMAGE_H
#define IMAGE_H


#include <iostream>
#include <map>

#include <chrono>
#include <ctime>



#include <Magick++.h>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "mwpath.h"
#include "mwresolution.h"
#include "utils.h"

namespace mw {

  using namespace boost::filesystem;

  static const string PIXEL_SPACING_KEY_WORD = "pixelspacing";

  static const double INCH = 25.4; // 1 inch = 25.4 milimieters

  static const vector<string> BAD__IMG_TYPES
                    {"XCF", "TXT", "PDF", "ICO"};


  class MagickPPExport MwImage: public Magick::Image
  {

   using Magick::Image::Image;


  public:

    using properties_map = std::map<string, string>;
    using sptr = shared_ptr<MwImage>;
    using uptr = unique_ptr<MwImage>;


    MwImage():Magick::Image() {};
    MwImage(const Magick::Image & image_);
    MwImage(const path &i_path);
    MwImage(const MwPath & i_path);
    MwImage(const string & i_path);

    //copy constructor
    MwImage( const MwImage & other);

    //copy assignment
    MwImage & operator=(const MwImage & other);

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

    void calcResolution();

    const MwResolution & getResolution() const {return resolution;}

    bool isDCM() const {return getType() == "DCM";}

    void  ping ( const path & image_path );

    bool is_any_type(const vector<string> & types) const;
    bool is_any_type(const string & types) const;



    virtual ~MwImage();

    static bool is_image(const path & img_path_, const uptr &pimage_);
    //static MwImage is_image(const path & img_path_);


  protected:

    MwPath img_path {};
    friend ostream & operator<<(ostream & os, const MwImage & img);

    properties_map properties {};
    MwResolution resolution {};

  };

}


#endif // IMAGE_H
