#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <sstream>
#include <vector>
#include <regex>


#include <boost/filesystem.hpp>

#include "infix_iterator.h"

namespace  mw {

  namespace bf = boost::filesystem;


  /**
   * Prints message in red in console.
   */
  template <typename T>
  inline void errp(const T & msg)
  {
      std::cout << "\033[1;31m" << mgs <<"\033[0m" << std::endl;
  }

  /**
   * Prints message in green in console.
   */
  template <typename T>
  inline void wrrp(const T & msg)
  {
      std::cout << "\033[1;32m" << msg <<"\033[0m" << std::endl;
  }


  /**
   * Splits a string on a given delim
   *
   * @brief split
   * @param s
   * @param delim
   * @return
   */
  std::vector<std::string>
  split(const std::string &s, char delim = ',')
  {

      std::vector<std::string> elems;

      std::stringstream ss(s);
      std::string item;
      while (std::getline(ss, item, delim))
      {
              elems.push_back(item);
      }
      return elems;
  }

  /**
   * Split a string on a given regular expression
   *
   * @brief resplit
   * @param s
   * @param rgx_str
   * @return
   */
  std::vector<std::string>
  resplit(const std::string & s, std::string rgx_str = R"(\s+)")
  {

      std::vector<std::string> elems;

      std::regex rgx (rgx_str);

      std::sregex_token_iterator iter(s.begin(), s.end(), rgx, -1);
      std::sregex_token_iterator end;

      while (iter != end)
      {
          elems.push_back(*iter);
          ++iter;
      }

      return elems;
  }

  /**
   * prints an iterable such as vector
   */
  template<typename T>
  void print_iterable(const T & elems) {

    infix_ostream_iterator<typename T::value_type>
              oiter(std::cout, ",");

    std::cout << "[";
    std::copy(elems.begin(), elems.end(),oiter);
    std::cout << "]" << std::endl;


  }

  /**
   * Joints an interable into a string using
   * given delim.
   */
  template<typename T>
  std::string join(const T & elems, char * delim = ",")
  {
      std::stringstream ss;

      typedef typename T::value_type elem_type;

      copy(elems.begin(), elems.end(),
           infix_ostream_iterator<elem_type>(ss, delim));

      return ss.str();
  }


  /**
   * Rounds a number with given precision.
   */
  template<typename T>
  T pround(T num, int p = 3)
  {
      return static_cast<T>(ceil( ( num * pow( 10, p ) ) - 0.49 ) / pow( 10,p ));
  }


  /**
   * Remove an extenstion from a file name.
   *
   * @brief removeExtension
   * @param filename
   * @return
   */
  std::string
  removeExtension(const std::string & filename)
  {


      size_t lastdot = filename.find_last_of(".");
      if (lastdot == std::string::npos) {
          return filename;
      }
      return filename.substr(0, lastdot);
  }


  /**
   * Remove an extenstion from a file name.
   *
   * @brief removeExtension
   * @param filename
   * @return
   */
  std::string removeExtension(const bf::path & filename)
  {
    return removeExtension(filename.string());
  }

}


#endif // UTILS_H

