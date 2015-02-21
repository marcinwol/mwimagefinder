#ifndef UTILS1_H
#define UTILS1_H

#include <iostream>
#include <sstream>
#include <vector>
#include <regex>



#include <boost/filesystem.hpp>

#include "infix_iterator.h"

namespace  mw {

  using namespace std;
  namespace bf = boost::filesystem;


  constexpr double MEGABYTE() {return 1024.0*1024.0;}


  /**
   * Prints message in red in console.
   */
  template <typename T>
  inline void errp(const T & msg)
  {
      std::cout << "\033[1;31m" << msg <<"\033[0m" << std::endl;
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
  split(const std::string &s, char delim = ',');


  /**
   * Split a string on a given regular expression
   *
   * @brief resplit
   * @param s
   * @param rgx_str
   * @return
   */
  std::vector<std::string>
  resplit(const std::string & s, std::string rgx_str = R"(\s+)");

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
   * Joints an interable into a string   using
   * given delim.
   */
  template<typename T>
  std::string join(const T & elems, const  char * delim = ",")
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
  removeExtension(const std::string & filename);


  /**
   * Remove an extenstion from a file name.
   *
   * @brief removeExtension
   * @param filename
   * @return
   */
  std::string removeExtension(const bf::path & filename);

  /**
   * Filesystem utilities
   */
  namespace fs
  {

    vector<bf::path>
    get_all_paths(const bf::path & in_path,
                  bool show_progress = false);


    bool
    create_output_dir(const string & out_path,
                      bool remove_if_exist = false);

    /**
     * Get file size in MB
     *
     * @brief get_file_size
     * @param p
     * @return
     */
    double get_file_size(const bf::path & p);


  }

}


#endif // UTILS1_H

