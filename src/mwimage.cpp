#include "mwimage.h"



namespace mw {

  MwImage::MwImage(const MwPath & i_path)
    :Magick::Image(i_path.string())
  {
    img_path = i_path;
  }

  MwImage::MwImage(const path & i_path)
    :Magick::Image(i_path.string())
  {
    img_path = MwPath(i_path);
  }

  MwImage::MwImage(const Magick::Image & image_, const string & i_path)
    :Magick::Image(image_)
  {
    //const Magick::Options * opt = image_.constOptions();
    //img_path = mw::MwPath(opt->fileName());
      img_path = mw::MwPath(i_path);
  }

  MwImage::MwImage(const MwImage & other):
    Magick::Image(other)
  {
    cout << "Copy constructor" << endl;
  }

  MwImage::MwImage(const string &i_path)
    :Magick::Image(i_path)
  {
    img_path = MwPath(i_path);
  }


  MwImage & MwImage::operator=(const MwImage & other)
  {
    Magick::Image::operator=(other);
    //cout << "Copy assignment" << endl;
    img_path = other.img_path;
    return *this;
  }


  string MwImage::getType() const
  {
    return string(this->magick());
  }


  double MwImage::getDiskSize() const
  {
    return fs::get_file_size(getPath());
  }

  void MwImage::readProperties()
  {
    const char * property;
    const char * value;

    MagickCore::Image * core_image = this->image();


    this->properties["format"] = core_image->magick;

    (void) GetImageProperty(core_image,"exif:*");
    (void) GetImageProperty(core_image,"icc:*");
    (void) GetImageProperty(core_image,"iptc:*");
    (void) GetImageProperty(core_image,"xmp:*");

    ResetImagePropertyIterator(core_image);
    property=GetNextImageProperty(core_image);

    if (property != (const char *) NULL)
      {
          while (property != (const char *) NULL)
            {
              value = GetImageProperty(core_image, property);
              this->properties[property] =  value;
              property = GetNextImageProperty(core_image);
            }

      }

    // finally calculate pixel spacfing
    calcResolution();

  }

  void MwImage::calcResolution() {

      double ps_x = 0.0;
      double ps_y = 0.0;


      if (!isDCM()) {
          // if not DICOM dont do anything special. Just convert
          // normal density into pixel spacing.

          Magick::Geometry DPI = this->density();

          ps_x = DPI.width()  > 0.0 ? 25.4 / DPI.width()   : 0.0;
          ps_y = DPI.height() > 0.0 ? 25.4 / DPI.height()  : 0.0;

          this->resolution = mw::MwResolution(ps_x, ps_y);
          return;

      }

    // to store potential dcm properties for pixelSpacing
    vector<properties_map::value_type> found_properties;

    // first find if we have pixel spacing propertie
    for (const auto & kv: this->properties)
    {
        if (boost::icontains(kv.first, PIXEL_SPACING_KEY_WORD))
        {
            found_properties.push_back(kv);
        }
    }



    if (!found_properties.empty()) {
        // found PixelSpacing propertie,
        // most likly in a dicom file
        string pixel_spacing;

        pixel_spacing = found_properties.at(0).second;
        vector<string> spacing_values = mw::split(pixel_spacing, '\\');

        // trim whitespace
        std::for_each(spacing_values.begin(),
                     spacing_values.end(),
                     [](string & v){boost::trim(v);});

        //my::print_iterable(spacing_values);
        if (!spacing_values.empty()) {


            ps_x = boost::lexical_cast<double>(spacing_values.at(0));
            ps_y = boost::lexical_cast<double>(spacing_values.at(1));

        }
    } else {
        // no PixelSpacing property. probably not dicom
        // so not surprise. If so, use density information (DPI)
        // and calcate pixel spacing.

        Magick::Geometry DPI = this->density();

        ps_x = DPI.width()  > 0.0 ? 25.4 / DPI.width()   : 0.0;
        ps_y = DPI.height() > 0.0 ? 25.4 / DPI.height()  : 0.0;

       // cout << "DPI: "<< DPI.width() << "x" << DPI.height()<< endl;
        //cout << "PS from DPI: "<< ps_x << "x" << ps_y << endl

    }

      this->resolution = mw::MwResolution(ps_x, ps_y);


  }


  bool MwImage::is_any_type(const vector<string> & types) const
  {

    vector<string>::const_iterator  ai;

    ai = std::find(types.begin(), types.end(), getType());

    if (ai != types.end())
    {
        return true;
    }

    return false;
  }


  bool MwImage::is_any_type(const string & types_) const
  {
       vector<string> good_types {mw::split(types_, ',')};
       return is_any_type(good_types);
  }



  void  MwImage::ping ( const path & image_path )
  {

    this->img_path = image_path;
    ping(image_path.string());
    cout << "my ping" << image_path << endl;


  }

  MwImage::properties_map
  MwImage::getProperties() const
  {
    return this->properties;
  }

   bool MwImage::propertiesEmpty() const
   {
     return properties.empty();
   }


  MwImage::~MwImage()
  {

  }

  ostream& operator<<(ostream& os, const MwImage & img)
  {
    os << img.getPath() <<": " << img.getType()
       << " " << img.getDiskSize() << "MB";
    return os;
  }



  bool MwImage::is_image(const path & img_path_,
                         const uptr & pimage_ = nullptr)
  {

    try
    {


      Magick::Image img ;

  //    auto start_time = std::chrono::high_resolution_clock::now();
      img.ping(img_path_.string());
//      auto end_time = std::chrono::high_resolution_clock::now();
//
      //auto e_time = end_time - start_time;

     // auto t = std::chrono::duration_cast<std::chrono::milliseconds>(e_time);

    //  std::cout << img_path_ << "time " << t.count() << " to run.\n";


      if (pimage_)
      {
        *pimage_ = mw::MwImage(img, img_path_.string());
      }

      return true;
    }
    catch(Magick::Error & e)
    {
      return false;
    }
    catch(Magick::WarningCorruptImage & e)
    {
      return false;
    }
    catch(Magick::WarningCoder & e)
    {
       return false;
    }
  }

   pair<bool, string> MwImage::is_image(const path & img_path_)
   {
        Signature empty_signature;
        bool is_image = mw::is_image(img_path_.string(), &empty_signature);
        return make_pair(is_image, empty_signature.str());
   }

}

