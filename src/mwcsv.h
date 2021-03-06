#ifndef MWCSV_H
#define MWCSV_H


#include<iostream>
#include<fstream>
#include<vector>

#include <boost/filesystem.hpp>

#include "utils.h"


namespace mw {

  using namespace std;
  using namespace boost::filesystem;

  class mwcsv_writer
  {
  public:
    mwcsv_writer() = delete;
    mwcsv_writer(std::ofstream & of_, const char * delim_ = ",");


    template<typename T>
    void write(const T & elems);

    void write(const string & a_line);

    // overload function template for char[].
    template<typename T, int N>
    void write(T (&elems) [N])
    {
       for (int i = 0; i < N - 1 ; ++i) {
           of << elems[i] << delim;
       }
       of << elems[N-1] << endl;
    }


    virtual ~mwcsv_writer();

  protected:
    ostream & of;
    const char * delim;
  };


  class mwcsv_reader
  {
  public:
    mwcsv_reader() = delete;
    mwcsv_reader(const std::fstream& of_, const char * delim_ = ",");

    void readlines();


    vector<string>::const_iterator begin () const
    {
        return lines.begin();
    }

    vector<string>::const_iterator end () const
    {
        return lines.end();
    }


    virtual ~mwcsv_reader();

  protected:
    istream & ifs;
    const char * delim;
    vector<string> lines;

  };


}

#endif // MWCSV_H
