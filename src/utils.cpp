
#include "utils.h"

namespace  mw {
  using namespace std;
  namespace bf = boost::filesystem;


  /**
   * Splits a string on a given delim
   *
   * @brief split
   * @param s
   * @param delim
   * @return
   */
  std::vector<std::string>
  split(const std::string &s, char delim)
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
  resplit(const std::string & s, std::string rgx_str)
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


  namespace fs
  {

    vector<bf::path>
    get_all_paths(const bf::path & in_path, bool show_progress)
    {

      bf::recursive_directory_iterator dir {in_path}, dir_end;
      vector<bf::path> paths;

      size_t i {0};

      if (show_progress)
      {
        cout << "Reading files: " << endl;
      }


      while(dir != dir_end)
      {


          if( boost::filesystem::is_symlink(*dir))
          {
               dir.no_push();
          }

          try
          {
            if (bf::is_regular_file(*dir)){
                //cout << i <<": "<< *dir << endl;
                paths.push_back(*dir);
                ++i;
            }
            ++dir;
          } catch(bf::filesystem_error & e)
          {
                cout << e.what() << ": " << *dir;
                cout << " ... skipping." << *dir;
                cout << endl;
          }


          if (show_progress && (i % 100) == 0)
          {
              cout  << "\r" << "Read " << i << " files ..."
                    << flush;
          }
      }


      if (show_progress)
      {
        cout << endl
             << "Total number of files found is: "
             << paths.size()
             << endl;
      }

      return paths;
    }



    bool
    create_output_dir(const string & out_path, bool remove_if_exist)
    {

      try
      {

        if (bf::exists(out_path) && remove_if_exist == true)
        {
           // cout << "removing: " << out_path <<endl;
              bf::remove_all(out_path);
        }

       bf::create_directory(out_path);
       return true;

      } catch(const bf::filesystem_error & e)
      {
         errp(e.what());
      }
      return false;
    }

    bool
    create_output_dir(const bf::path & out_path, bool remove_if_exist)
    {
      return create_output_dir(out_path.string(),remove_if_exist);
    }


    /**
     * Get file size in MB
     *
     * @brief get_file_size
     * @param p
     * @return
     */
    double get_file_size(const bf::path & p)
    {

      double sizeMB = static_cast<double>(bf::file_size(p))/MEGABYTE();

      return round(sizeMB*100)/100;

    }



  }



}
