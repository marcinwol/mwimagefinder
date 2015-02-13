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

}

