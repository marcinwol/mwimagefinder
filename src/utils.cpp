
#include "utils.h"

#include <errno.h>
#include <fts.h>

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



      /** Scaning folder for all paths using fts_read linux method.
       * @brief fts_dear_tree_scan
       * @param in_path
       * @param found_paths
       * @return
       */
      int fts_dear_tree_scan(const string & in_path,
                            vector<string> & found_paths,
                            bool show_progress)
      {

          char * cstr = new char[in_path.length() + 1];
          strcpy(cstr, in_path.c_str());

          char * path[2] {cstr, nullptr};

          size_t i {0};


          FTS *tree = fts_open(path, FTS_NOCHDIR, 0);

          if (!tree)
          {
              delete[] cstr;
              perror("fts_open");
              return 1;
          }

          if (show_progress)
          {
            cout << "Reading files in " << in_path << endl;
          }


          FTSENT *node;

          while ((node = fts_read(tree)))
          {
              if (node->fts_level > 0 && node->fts_name[0] == '.')
              {
                  fts_set(tree, node, FTS_SKIP);

              }
              else if (node->fts_info & FTS_F)
              {
                  if (show_progress && (i % 100 == 0))
                  {
                      cout  << "\r" << "Read " << i << " files "
                            << "in " << in_path
                            << flush;
                  }

                  ++i;

                 found_paths.emplace_back<string>(node->fts_path);
              }
          }

          if (errno)
          {
              delete[] cstr;
              perror("fts_read");
              return 1;
          }

          if (fts_close(tree))
          {
              delete[] cstr;
              perror("fts_close");
              return 1;
          }

          delete[] cstr;
          return 0;
      }


      vector<bf::path>
      get_all_paths_fts(const bf::path & in_path, bool show_progress)
      {
           vector<bf::path> paths;
           vector<string> paths_str;

           int status {1};
           status = fts_dear_tree_scan(in_path.string(), paths_str, show_progress);

           if (status == 0)
           {
               paths.reserve(paths_str.size());
               for (const string & a_path_str : paths_str)
               {
                   paths.push_back(bf::path {a_path_str});
               }
           }


           return paths;
      }




    vector<bf::path>
    get_all_paths(const bf::path & in_path, bool show_progress)
    {

      bf::recursive_directory_iterator dir {in_path}, dir_end;
      vector<bf::path> paths;

      size_t i {0};

      if (show_progress)
      {
        cout << "Reading files in " << in_path << endl;
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
              cout  << "\r" << "Read " << i << " files "
                    << "in " << in_path
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

      return sizeMB;

    }



  }



}
