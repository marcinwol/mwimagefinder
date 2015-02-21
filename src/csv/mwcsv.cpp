#include "mwcsv.h"



namespace mw {


  mwcsv_writer::mwcsv_writer(ofstream & of_, const char *delim_)
    :of{of_}, delim {delim_}
  {
    cout <<"mwcsv_writer constructor"<< endl;
  }


  template<typename T>
  void mwcsv_writer::write(const T & elems)
  {
    string a_line = mw::join(elems, delim);
    of << a_line << endl;
  }

  // Explicit instantiation of the above template
  template void mwcsv_writer::write<>(const vector<string> & elems);






  // overload function for strings.
  void mwcsv_writer::write(const string & a_line) {
      of << a_line << endl;
  }




  mwcsv_writer::~mwcsv_writer()
  {

  }


}

