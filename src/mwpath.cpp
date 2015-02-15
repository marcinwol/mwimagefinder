#include "mwpath.h"

namespace mw {


  //copy constructor
//  MwPath::MwPath( const MwPath & other)
//    :boost::filesystem::path(other)
//  {

//  }

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

