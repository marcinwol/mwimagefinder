#include "mwcsv.h"



namespace mw {


  mwcsv_writer::mwcsv_writer(ofstream & of_):of{of_}
  {
    cout <<"mwcsv_writer constructor"<< endl;
  }



  void mwcsv_writer::write(const string & line)
  {
    of << line << endl;
  }




  mwcsv_writer::~mwcsv_writer()
  {
    of.close();
  }


}

