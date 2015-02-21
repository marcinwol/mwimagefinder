#ifndef MWRESOLUTION_H
#define MWRESOLUTION_H


#include <iostream>
#include <sstream>
#include <vector>
#include <array>
#include <algorithm>
#include <map>
#include <memory>

#include <Magick++.h>
#include <magick/MagickCore.h>

#include <boost/optional.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>

#include "utils.h"

namespace mw {

    class MwResolution
    {
    public:
        MwResolution(double ps_x=0.0, double ps_y=0.0):x{ps_x},y{ps_y} {}
        MwResolution(const MwResolution & other);
        MwResolution & operator=( const MwResolution & other );
        MwResolution & operator=(MwResolution && other);

        array<double, 2> getPS() const;
        array<double, 2> getDPI() const;

        bool operator==(const MwResolution & other);
        ~MwResolution();
    private:
      double x {0.0}; // Pixel Spacing [mm] in x direction e.g. 0.14 mm
      double y {0.0}; // Pixel Spacing y
      friend ostream & operator<<(ostream & os, const MwResolution & res);
    };
}

#endif // MWRESOLUTION_H
