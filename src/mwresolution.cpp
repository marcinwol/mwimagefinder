#include "mwresolution.h"

namespace mw {


    MwResolution::MwResolution(const MwResolution & other)
    {
      //cout << "Call copy constructor" << endl;
      x = other.x;
      y = other.y;
    }

    MwResolution & MwResolution::operator=( const MwResolution & other )
    {
         // cout << "Call copy assignment" << endl;
          x = other.x;
          y = other.y;
          return *this;
    }


    array<double, 2> MwResolution::getPS() const
    {
      return array<double,2> {x, y};
    }


    MwResolution & MwResolution::operator=(MwResolution && other)
    {
     // cout << "Call move assignment" << endl;
      x = std::move(other.x);
      y = std::move(other.y);
      return *this;
    }

    bool MwResolution::operator==(const MwResolution & other)
    {
      //cout << "equal to operatora" << endl;
      return x == other.x && y == other.y;
    }

    MwResolution::~MwResolution()
    {

    }


    ostream & operator<<(ostream & os, const MwResolution & res)
    {
      os << res.x <<"x"<< res.y ;
      return os;
    }


}

