#ifndef UTILS1_H
#define UTILS1_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#if GCC_VERSION > 40900
    #include <regex>
#else
    #include <boost/regex.hpp>
#endif



    #include <boost/filesystem.hpp>

#include "../ext/infix_iterator.h"

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

  bool
  replace(std::string& str, const std::string& from, const std::string& to);

  std::string
  replaceall(std::string str, const std::string& from, const std::string& to);


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



  std::vector<string>
  readlines(istream & in_file);


  template <typename T>
  std::vector<string>
  readlines(const T & in_file);




  /**
   * Joints an interable into a string   using
   * given delim.
   */
  template<typename T>
  std::string
  join(const T & elems, const  char * delim = ",")
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

  std::string
  extract_first_number(const std::string & in_str);    


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

     const bool OVERWRITE_IF_EXIST {true};

     /** Scaning folder for all paths using fts_read linux method.
     *
     * @brief fts_dear_tree_scan
     * @param in_path
     * @param found_paths
     * @return
     */
    int fts_dear_tree_scan(const string & in_path,
                                vector<string> & found_paths,
                                bool show_progress = false);

    vector<bf::path>
    get_all_paths_fts(const bf::path & in_path,
                             bool show_progress = false);

    /** Using boost::filesystem
     *
     * @brief get_all_paths
     * @param in_path
     * @param show_progress
     * @return
     */
    vector<bf::path>
    get_all_paths(const bf::path & in_path,
                  bool show_progress = false);


    bool
    create_output_dir(const string & out_path,
                      bool remove_if_exist = false);

    bool
    create_output_dir(const bf::path & out_path, bool remove_if_exist);

    /**
     * Get file size in MB
     *
     * @brief get_file_size
     * @param p
     * @return
     */
    double get_file_size(const bf::path & p);

    std::string
    clean_file_path(const string & in_path,
                    const boost::regex & rexp = boost::regex {R"([\s_,\.\/]+)"},
                    const string & substr = "_");
    std::string
    clean_file_path(const bf::path & in_path,
                    const boost::regex & rexp = boost::regex {R"([\s_,\.\/]+)"},
                    const string & substr = "_");



  }

}


#endif // UTILS1_H

