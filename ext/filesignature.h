#ifndef FILESIGNATURE_H
#define FILESIGNATURE_H

#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <sstream>
#include <iomanip>

#include <string.h>
#include <errno.h>


#define IMAGE_ENUM(DO) \
  DO(UNKOWN) \
  DO(ASCII)  \
  DO(BMP)    \
  DO(CHM)    \
  DO(DB)     \
  DO(DIB)    \
  DO(DLL)    \
  DO(DCM)    \
  DO(DOCX)   \
  DO(EXE)    \
  DO(GIF)    \
  DO(HTML)   \
  DO(ICO)    \
  DO(ICNS)   \
  DO(JPEG)   \
  DO(MAT)    \
  DO(MACHO)  \
  DO(MP)     \
  DO(NEF)    \
  DO(PDF)    \
  DO(PNG)    \
  DO(PPTX)   \
  DO(PSD)    \
  DO(TIFF)   \
  DO(XCF)    \
  DO(XLSX)   \
  DO(XML)    \
  DO(ZIP)

#define MAKE_ENUM(VAR) VAR,

#define MAKE_STRINGS(VAR) #VAR,

#ifndef SIGNATURE_SET_NAME
    #define SIGNATURE_SET_NAME known_signatures
#endif

#ifndef BRACED_INIT_LIST
    #define BRACED_INIT_LIST(...) {__VA_ARGS__}
#endif

#ifndef ADD_SIGNATURE
    #define ADD_SIGNATURE(sig, im_type, is_image) \
          SIGNATURE_SET_NAME.emplace<vector<unsigned char>, IMAGE_TYPES> \
                    (BRACED_INIT_LIST sig, im_type, is_image);
#endif



namespace mw {

  using namespace std;

  struct Signature;

  using signature_set       = multiset<Signature>;
  using signature_set_iter  = multiset<Signature>::iterator;
  using signature_set_riter = multiset<Signature>::reverse_iterator;



  enum class IMAGE_TYPES
  {
    IMAGE_ENUM(MAKE_ENUM)
  };


  const char* const
  IMAGE_TYPES_NAMES[] =
  {
    IMAGE_ENUM(MAKE_STRINGS)
  };

  inline const char *
  GET_TYPE_NAME(IMAGE_TYPES type)
  {
      return IMAGE_TYPES_NAMES[static_cast<int>(type)];
  }

  inline int
  GET_TYPE_VALUE(IMAGE_TYPES type)
  {
      return static_cast<int>(type);
  }



  struct Signature
  {
     vector<unsigned char> sig;
     IMAGE_TYPES img_type;
     bool is_image;

     Signature();

     Signature(const vector<unsigned char> & sig_,
               const IMAGE_TYPES & img_type_ = IMAGE_TYPES::UNKOWN,
               bool is_image_ = false);

     Signature( const Signature & other );
     Signature & operator=(const Signature & other);

     bool operator <  (const Signature & other) const;
     bool operator == (const Signature & other) const;
     operator bool () const;

     string str() const;
     int val() const;

  };


  set<int>
  get_known_signatures_lengths();

  string
  get_signature_as_string(const vector<unsigned char> & signature);


  vector<unsigned char>
  get_bin_signature(const string & in_file, int length = 132);

  bool
  is_ascii(const string & in_file, vector<mw::Signature> & sig_holder);


  bool
  detect_type(const string & a_path, vector<mw::Signature> & sig_holder);

  bool
  is_image(const string & a_path, mw::Signature * sig_holder = nullptr);


  /**
   * @brief returns a reference to the multiset of signatures containing known signatures.
   *        New signatures are compared against this set to determine the file type.
   * @return
   */
  inline signature_set &
  get_known_signatures()
  {
      static signature_set SIGNATURE_SET_NAME;

      if (!SIGNATURE_SET_NAME.empty())
      {
          return SIGNATURE_SET_NAME;
      }

      ADD_SIGNATURE((0x42, 0x4D),             IMAGE_TYPES::BMP,   true);

      ADD_SIGNATURE((0x42, 0x4D),             IMAGE_TYPES::CHM,   false);

      ADD_SIGNATURE((0xD0, 0xCF, 0x11, 0xE0,
                     0xA1, 0xB1, 0x1A, 0xE1,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00), IMAGE_TYPES::DB,    false);

      ADD_SIGNATURE((0x49, 0x54, 0x53, 0x46), IMAGE_TYPES::DIB,   false);

      ADD_SIGNATURE((0x4D, 0x5A),             IMAGE_TYPES::DLL,   false);


      ADD_SIGNATURE((0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x44, 0x49, 0x43, 0x4D), IMAGE_TYPES::DCM,    true);

      ADD_SIGNATURE((0x50, 0x4B, 0x03, 0x04,
                     0x14, 0x00, 0x06, 0x00), IMAGE_TYPES::DOCX,   false);

      ADD_SIGNATURE((0x4D, 0x5A, 0x90, 0x00,
                     0x03, 0x00, 0x00, 0x00,
                     0x04, 0x00, 0x00, 0x00,
                                 0xFF, 0xFF), IMAGE_TYPES::EXE,    false);



      ADD_SIGNATURE((0x47, 0x49, 0x46, 0x38,
                                 0x37, 0x61), IMAGE_TYPES::GIF,    true);

      ADD_SIGNATURE((0x47, 0x49, 0x46, 0x38,
                                 0x39, 0x61), IMAGE_TYPES::GIF,    true);

      ADD_SIGNATURE((0x3C, 0x21),             IMAGE_TYPES::HTML,   false);

      ADD_SIGNATURE((0x00, 0x00, 0x01, 0x00), IMAGE_TYPES::ICO,    true);

      ADD_SIGNATURE((0x69, 0x63, 0x6E, 0x73), IMAGE_TYPES::ICNS,   true);

      ADD_SIGNATURE((0xFF, 0xD8, 0xFF, 0xE1), IMAGE_TYPES::JPEG,   true);
      ADD_SIGNATURE((0xFF, 0xD8, 0xFF, 0xE0), IMAGE_TYPES::JPEG,   true);
      ADD_SIGNATURE((0xFF, 0xD8, 0xFF, 0xE8), IMAGE_TYPES::JPEG,   true);

      ADD_SIGNATURE(( 0x4D, 0x41, 0x54, 0x4C,
                      0x41, 0x42, 0x20, 0x35,
                      0x2E, 0x30, 0x20, 0x4D,
                      0x41, 0x54, 0x2D, 0x66,
                      0x69, 0x6C, 0x65),      IMAGE_TYPES::MAT,    false);


      ADD_SIGNATURE((0xCE, 0xFA, 0xED, 0xFE), IMAGE_TYPES::MACHO, false);

      ADD_SIGNATURE((0x0C, 0xED),             IMAGE_TYPES::MP,     false);

      ADD_SIGNATURE((0x4D, 0x4D, 0x00, 0x2A,
                     0x00, 0x00, 0x00, 0x08,
                                       0x00), IMAGE_TYPES::NEF,    true);

      ADD_SIGNATURE((0x49, 0x49, 0x2A, 0x00,
                     0x08, 0x00, 0x00, 0x00,
                                       0x1A), IMAGE_TYPES::NEF,    true);

      ADD_SIGNATURE((0x25, 0x50, 0x44, 0x46), IMAGE_TYPES::PDF,    false);

      ADD_SIGNATURE((0x89, 0x50, 0x4E, 0x47,
                     0x0D, 0x0A, 0x1A, 0x0A), IMAGE_TYPES::PNG,    true);

      ADD_SIGNATURE((0x50, 0x4B, 0x03, 0x04,
                     0x14, 0x00, 0x06, 0x00), IMAGE_TYPES::PPTX,   false);

      ADD_SIGNATURE((0x38, 0x42, 0x50, 0x53), IMAGE_TYPES::PSD,    true);

      ADD_SIGNATURE((0x49, 0x20, 0x49),       IMAGE_TYPES::TIFF,   true);
      ADD_SIGNATURE((0x4D, 0x4D, 0x00, 0x2A), IMAGE_TYPES::TIFF,   true);
      ADD_SIGNATURE((0x4D, 0x4D, 0x00, 0x2B), IMAGE_TYPES::TIFF,   true);
      ADD_SIGNATURE((0x49, 0x49, 0x2A, 0x00), IMAGE_TYPES::TIFF,   true);

      ADD_SIGNATURE((0x67, 0x69, 0x6D, 0x70,
                     0x20, 0x78, 0x63, 0x66,
                     0x20, 0x66, 0x69, 0x6C,
                                       0x65), IMAGE_TYPES::XCF,    true);

      ADD_SIGNATURE((0x50, 0x4B, 0x03, 0x04,
                     0x14, 0x00, 0x06, 0x00), IMAGE_TYPES::XLSX,   false);

      ADD_SIGNATURE((0x3C                  ), IMAGE_TYPES::XML,    false);


      ADD_SIGNATURE((0x50, 0x4B, 0x03, 0x04), IMAGE_TYPES::ZIP,    false);




      return SIGNATURE_SET_NAME;
  }



  inline set<int>
  get_known_signatures_lengths()
  {
      signature_set sig_set = get_known_signatures();

      static set<int> sig_lengths;

      if (!sig_lengths.empty())
      {
          return sig_lengths;
      }

      for (const Signature & sig: sig_set)
      {
            sig_lengths.insert(sig.sig.size());
      }

      return sig_lengths;
  }




 }


#undef IMAGE_ENUM
#undef MAKE_ENUM
#undef MAKE_STRINGS

#endif // FILESIGNATURE_H
