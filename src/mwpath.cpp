#include "mwpath.h"

namespace mw {

  MwPath::MwPath():boost::filesystem::path() {

  }


  //copy constructor
  MwPath::MwPath( const MwPath & other)
    :boost::filesystem::path(other)
  {
        //cout << "Copy constructor" << endl;

  }

  //copy assignment
  MwPath & MwPath::operator=(const MwPath & other)
  {
    boost::filesystem::path::operator =(other);
    //cout << "Copy assignment 1" << endl;
    return *this;
  }


  MwPath::~MwPath()
  {

  }

}

