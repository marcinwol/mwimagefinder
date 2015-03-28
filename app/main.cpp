#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define BOOST_NO_CXX11_SCOPED_ENUMS

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

#include "../ext/format.h"

#include "utils.h"
#include "imagefinderoptions.h"
#include "mwimage.h"
#include "mwpath.h"
#include "csv/mwcsv.h"



using namespace std;
using namespace boost::filesystem;



int main(int ac, char* av[])
{


    mw::ImageFinderOptions po {ac, av};

    if (!po.parse_options())
    {
        return 1;
    }

    bool verbose              {po.get<bool>("verbose")};
    vector<string> in_dirs    {po.get<vector<string>>("in-dir")};
    path out_dir              {po.get<string>("out-dir")};
    path path_file            {po.get<string>("path-file")};
    path out_csv              {po.get<string>("csv-file")};
    path output_dir           {po.get<string>("out-dir")};
    string file_type          {po.get<string>("file-type")};
    string file_size          {po.get<string>("file-size")};
    vector<string> file_types {mw::split(file_type, ',')};
    bool fast_scan            {po.get<bool>("fast")};
    bool detailed             {po.get<bool>("detailed")};
    bool copy_files           {!output_dir.empty()};



    if (in_dirs.empty())
    {
      in_dirs.push_back(current_path().string());
    }
    else
    {
      for (const string & in_dir : in_dirs)
      {
        if (!exists(path(in_dir)))
        {
          fmt::print_colored(fmt::RED, "Folder \"{}\" does not exist.\n", in_dir);
          return 1;
        }
      }
    }

    mw::ImageFinderOptions::size_opt fsize= po.get_file_size_option();


    if (out_csv.empty())
    {
         out_csv = path {current_path() / path("found_files.csv")};
    }

    if (detailed == true)
    {
        fast_scan = false;
    }

    if (!mw::fs::create_output_dir(output_dir, mw::fs::OVERWRITE_IF_EXIST))
    {
        return 1;
    }


    cout << "out_csv: " << out_csv << endl;


    size_t imgNo  {0};
    size_t fileNo {0};
    size_t totalPathNo {0};



    // read all paths from input folders into
    // one vector for paths
    vector<pair<path,vector<path>>> all_paths {};

    for (const string & in_dir : in_dirs)
    {
      vector<path> found_paths = mw::fs::get_all_paths_fts(in_dir, true);
      all_paths.push_back(make_pair(path(in_dir), found_paths));    
      totalPathNo += found_paths.size();
    }


    // save results to the output csv file
    ofstream of {out_csv.string()};
    if (!of)
    {
      mw::errp(out_csv.string() + " creation failed!");
    }

    mw::mwcsv_writer f {of};

    vector<string> header {"In_dir", "File", "Type", "Size[MB]"};

    if (fast_scan == false)
    {
      header.push_back("ps_x[mm]");
      header.push_back("ps_y[mm]");
      header.push_back("DPIx");
      header.push_back("DPIy");
    }

    f.write(header);


    vector<string> a_line {8};
    vector<vector<string>> all_lines;


    // check if found files are images, i.e. if they
    // are recognized by ImageMagick++. If yes, then
    // read their properties and save to csv file.

    set<string> prop_set {};

    for (size_t i = 0; i < all_paths.size(); ++i)
    {

      const pair<path, vector<path>> & found_paths = all_paths[i];
      const path & in_path = found_paths.first;
      const vector<path> & found_files = found_paths.second;

      for (size_t j = 0; j < found_files.size(); ++j)
      {
          const path & t = found_files[j];

          ++fileNo;

          if (verbose)
          {
            fmt::print("{}/{}: Analyzing {}...", fileNo, totalPathNo, t.filename());
          }
          else
          {
              if (j % 10 == 0)
              {
                  fmt::print("\rAnalyzed {}/{} files in {} ...",
                             fileNo, totalPathNo, in_path);

                  cout << flush;
              }
          }


          double img_size = mw::fs::get_file_size(t);

          // use image file size option if provided
          using size_cmp =  mw::ImageFinderOptions::IMG_SIZE_CMP;

          if (fsize.first != size_cmp::NONE)
          {
              if (fsize.first == size_cmp::LO)
              {
                  if (img_size > fsize.second.at(0))
                    {
                      continue;
                    }
              }
              else if (fsize.first == size_cmp::GT)
              {
                  if (img_size < fsize.second.at(0))
                    {
                      continue;
                    }
              }
              else if (fsize.first == size_cmp::GL)
                {
                    if (img_size < fsize.second.at(0) || img_size > fsize.second.at(1))
                      {
                        continue;
                      }
                }
          }



          pair<bool, string> file_type = mw::MwImage::is_image(t);


          if (!file_type.first) {
             // if not an image type
              if (verbose)
              {
                fmt::print(" not an image: {}\n",  file_type.second);
              }
             continue;
          }                    

          string img_type {file_type.second};

          if (!file_types.empty())
          {
              // if file_types provided by the user, check if we have
              // one of the types requested
              if (std::find(file_types.begin(), file_types.end(), img_type) == file_types.end())
              {
                  // not found, then continue
                  if (verbose)
                  {
                    fmt::print(" image found but not of interest: {}\n",  img_type);
                  }
                  continue;
              }

          }

          // so here we have image file of interest. Thus, create
          // pointer to hold our image and use is_image version
          // that uses ImageMagick. This assures that our image
          // is good, not damaged for example.

          a_line[0] = "\""+in_path.string()+"\"";
          a_line[1] = "\""+t.string()+"\"";
          a_line[2] = img_type;
          a_line[3] = to_string(img_size);

          if (fast_scan == false)
          {
              mw::MwImage::uptr img_ptr {new mw::MwImage{}};

              if (!mw::MwImage::is_image(t, img_ptr))
              {
                  if (verbose)
                  {
                    fmt::print("ERROR rading: {}. skipping ...", t);
                  }
                  continue;
              }

              img_type =  img_ptr->getType();

              img_ptr->readProperties();

              const mw::MwResolution res = img_ptr->getResolution();

              a_line[4] = to_string(res.getPS()[0]);
              a_line[5] = to_string(res.getPS()[1]);
              a_line[6] = to_string(res.getDPI()[0]);
              a_line[7] = to_string(res.getDPI()[1]);


             const mw::MwImage::properties_map & props
                 = img_ptr->getProperties();

             if (detailed == true)
             {
                 a_line.erase(a_line.begin()+8, a_line.end());

                 for (const auto & kv: props)
                 {
                     string prop_name = kv.first;
                     string prop_value = kv.second;
                     replace(prop_name.begin(), prop_name.end(), '"', '\'');
                     replace(prop_value.begin(), prop_value.end(), '"', '\'');

                     boost::trim(prop_name);
                     boost::trim(prop_value);

                     a_line.emplace_back<string>(fmt::format("\"{}|{}\"",
                                                             prop_name, prop_value));
                     prop_set.insert(prop_name);
                 }
             }

          }


          f.write(a_line);

          all_lines.push_back(a_line);

          if (verbose)
          {
            fmt::print(" is image: {}.\n",  img_type);
            fmt::print("{}\n", mw::join(a_line));
          }

          if (copy_files)
          {


              string f_extension {boost::filesystem::extension(t)};

              string t_str {t.string()};

              mw::replace(t_str, in_path.string(),"");
              mw::replace(t_str, f_extension,"");
              t_str = mw::fs::clean_file_path(t_str);

              string filename {t_str};
              filename += "." + boost::algorithm::to_lower_copy(img_type);

              path out_filename {output_dir / path(filename)};


              // cout << t << endl;
              // cout << mw::fs::clean_file_path(t_str) << endl;
              // cout << out_filename << endl << endl;


              try
              {
                copy_file(t, out_filename, copy_option::overwrite_if_exists);
              }
              catch (filesystem_error & e)
              {
                  cerr << e.what() << endl;
              }
          }


          ++imgNo;

      } //  for (size_t j = 0; j < found_files.size(); ++j)
    } // for (size_t i = 0; i < all_paths.size(); ++i)

    of.close();




    fmt::print("\n");
    fmt::print("Found {} images out of {} files analyzed\n", imgNo, totalPathNo);
    fmt::print("CSV file saved in: {}\n", out_csv);


    if (detailed == true)
    {
        fmt::print("Reorganizing the csv file to account for all image properties found\n");

        path tmp_file = temp_directory_path() / unique_path();

        ofstream new_csv  {tmp_file.string()};

        mw::mwcsv_writer f2 {new_csv};

        vector<string> new_header = header;

        for (const string & prop_name: prop_set)
        {
            new_header.push_back(fmt::format("\"{}\"", prop_name));
        }



        f2.write(new_header);


        for (const vector<string> & l: all_lines)
        {
            map<string, string> pvs;

            for (size_t i = 8; i < l.size(); ++i)
            {
                string cell_value = l.at(i);

                cell_value.erase(0, 1);
                cell_value.erase(cell_value.end()-1);

                vector<string> pv = mw::split(cell_value, '|');

                if (pv.size() > 1)
                {
                    pvs[pv.at(0)] = pv.at(1);
                }
                else
                {
                    pvs[pv.at(0)] = "";
                }

            }

            vector<string> new_line(l.begin(), l.begin()+8);

            for (const string & key: prop_set)
            {

                if (pvs.find(key) != pvs.end())
                {
                    new_line.push_back(fmt::format("\"{}\"", pvs[key]));
                }
                else
                {
                    new_line.push_back(string{});
                }

            }

            f2.write(new_line);
        }

        new_csv.close();

        // if tmp file created, than substitite the csv file with full properites.
        try
        {
            boost::filesystem::copy_file(path(tmp_file), out_csv, copy_option::overwrite_if_exists);
        }
        catch (filesystem_error & e)
        {
            cerr << e.what() << endl;
        }

        remove(tmp_file);

    }

    return 0;
}
