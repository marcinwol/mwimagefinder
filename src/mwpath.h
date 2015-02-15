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

    //copy constructor
   // MwPath( const MwPath & other);

    //copy assignment
    MwPath & operator=(const MwPath & other);

   virtual ~MwPath();
  };

}

#endif // PATH_H
