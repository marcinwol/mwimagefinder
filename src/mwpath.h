#ifndef PATH_H
#define PATH_H

#include <iostream>

#include <boost/filesystem.hpp>


namespace mw {


  using namespace std;
  using namespace boost::filesystem;

  class MwPath: public boost::filesystem::path
  {

    using boost::filesystem::path::path;

  public:
   virtual ~MwPath();
  };

}

#endif // PATH_H
