#ifndef PATH_H
#define PATH_H

#include <iostream>

#include <boost/filesystem.hpp>


namespace mw {


  using namespace std;
  using namespace boost::filesystem;

  class Path: public boost::filesystem::path
  {

    using boost::filesystem::path::path;

  public:
   virtual ~Path();
  };

}

#endif // PATH_H
