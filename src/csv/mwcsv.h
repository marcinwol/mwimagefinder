#ifndef MWCSV_H
#define MWCSV_H


#include<iostream>
#include<fstream>
#include<vector>

#include <boost/filesystem.hpp>


namespace mw {

  using namespace std;
  using namespace boost::filesystem;

  class mwcsv_writer
  {
  public:
    mwcsv_writer() = delete;
    mwcsv_writer(ofstream & of_);

    void write(const string & line);

    virtual ~mwcsv_writer();
  protected:
    ofstream & of;
  };






}

#endif // MWCSV_H
