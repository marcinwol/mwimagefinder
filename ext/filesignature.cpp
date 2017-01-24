#include "filesignature.h"

namespace mw {

  Signature::Signature():
    sig {}, img_type {IMAGE_TYPES::UNKOWN}, is_image {false}
  {}

  Signature::Signature(const vector<unsigned char> & sig_,
                       const IMAGE_TYPES & img_type_,
                       bool is_image_):
      sig {sig_}, img_type {img_type_}, is_image {is_image_}
  {}


  Signature::Signature( const Signature & other ):
    sig {other.sig}, img_type {other.img_type}, is_image {other.is_image}
  {}

  Signature & Signature::operator=(const Signature & other)
  {
      sig      = other.sig;
      img_type = other.img_type;
      is_image = other.is_image;

      return *this;
  }

  bool Signature::operator < (const Signature & other) const
  {
        return sig < other.sig;
  }

  bool Signature::operator == (const Signature & other) const
  {
        return sig == other.sig;
  }


  Signature::operator bool () const
  {
    return img_type != IMAGE_TYPES::UNKOWN && is_image == true;
  }

  string Signature::str() const
  {
    return GET_TYPE_NAME(img_type);
  }

  int Signature::val() const
  {
    return GET_TYPE_VALUE(img_type);
  }

  bool
  is_ascii(const string & in_file, vector<Signature> & sig_holder) {
      int c;
      std::ifstream ifs(in_file);

      if (!ifs)
      {
        return false;
      }

      while((c = ifs.get()) != EOF && c <= 127);
      if(c == EOF)
      {

          sig_holder.push_back(Signature {{}, IMAGE_TYPES::ASCII});
          return true;
      }

      return false;

  }


  bool detect_type(const string & a_path, vector<mw::Signature> & sig_holder)
  {
      mw::signature_set known_sigs    = mw::get_known_signatures();
      set<int> sig_lengths            = mw::get_known_signatures_lengths();

      vector<unsigned char> signature = mw::get_bin_signature(a_path);

      if (signature.empty())
      {
          return false;
      }


      for (set<int>::reverse_iterator rit =  sig_lengths.rbegin();
                                      rit != sig_lengths.rend();
                                      ++rit)
      {
          int sig_length = *rit;

          vector<unsigned char> v_partial(signature.begin(),
                                          signature.begin() + sig_length);

         // cout << sig_length <<": " << mw::get_signature_as_string(v_partial);
         // cout << endl;


          pair< mw::signature_set_iter,  mw::signature_set_iter> search_result
                  = known_sigs.equal_range(v_partial);
          for (mw::signature_set_iter i = search_result.first;
                                      i != search_result.second;
                                      ++i)
          {
              sig_holder.push_back(*i);
          }

      }

      return !sig_holder.empty();
  }

  bool
  is_image(const string & a_path, mw::Signature * sig_holder)
  {
      vector<mw::Signature>  found_sigs;

      if (mw::detect_type(a_path, found_sigs))
      {
          for (const mw::Signature & found_sig : found_sigs)
          {
              // if signature is an image
              if (found_sig)
              {
                if (sig_holder)
                {
                  *sig_holder = found_sig;
                }
                return true;
              }
          }
      }

      return false;
  }


  vector<unsigned char>
  get_bin_signature(const string & in_file, int length)
  {

      vector<unsigned char> signature;

      ifstream ifs {in_file, ios_base::binary};

      if (!ifs)
      {          
          cerr << "Error : get_bin_signature: "
               << strerror(errno) << endl;
          return signature;
      }

      char bytes[length];

      ifs.read(bytes, length);

      signature.assign(bytes, bytes + length);

      return signature;
  }


  string
  get_signature_as_string(const vector<unsigned char> & signature)
  {
      ostringstream oss;

      oss << setfill('0')  << uppercase;

      for (const unsigned char & ps: signature)
      {
          oss << hex << setw(2) << static_cast<unsigned>(ps)<< " ";
      }

      return oss.str();

  }



}
