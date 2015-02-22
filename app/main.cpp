#include <iostream>
#include <fstream>
#include <vector>

#include <boost/filesystem.hpp>

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

    if (!po.parse_options()) {
        return 1;
    }

    bool verbose              {po.get<bool>("verbose")};
    vector<string> in_dirs    {po.get<vector<string>>("in-dir")};
    path out_dir              {po.get<string>("out-dir")};
    path path_file            {po.get<string>("path-file")};
    path out_csv              {po.get<string>("csv-file")};
    string file_type          {po.get<string>("file-type")};
    vector<string> file_types {mw::split(file_type, ',')};

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


    if (out_csv.empty()) {
         out_csv = path {current_path() / path("found_files.csv")};
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
      vector<path> found_paths = mw::fs::get_all_paths(in_dir, true);
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

    string header[] = {"In_dir", "File", "Type", "Size[MB]",
                       "ps_x[mm]", "ps_y[mm]",
                       "DPIx", "DPIy"};
    f.write(header);

    vector<string> a_line {8};


    // check if found files are images, i.e. if they
    // are recognized by ImageMagick++. If yes, then
    // read their properties and save to csv file.
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

          mw::MwImage::uptr img_ptr = make_unique<mw::MwImage>();

          if (mw::MwImage::is_image(t, img_ptr))  {

              if (!file_types.empty() && !img_ptr->is_any_type(file_types))
              {
                continue;
              }

              img_ptr->readProperties();

              const mw::MwResolution & res = img_ptr->getResolution();

              a_line[0] = "\""+in_path.string()+"\"";
              a_line[1] = "\""+img_ptr->getPath().string()+"\"";
              a_line[2] = img_ptr->getType();
              a_line[3] = to_string(img_ptr->getDiskSize());
              a_line[4] = to_string(res.getPS()[0]);
              a_line[5] = to_string(res.getPS()[1]);
              a_line[6] = to_string(res.getDPI()[0]);
              a_line[7] = to_string(res.getDPI()[1]);

              f.write(a_line);

              if (verbose)
              {
                fmt::print(" is image: {}.\n",  img_ptr->magick());
                fmt::print("{}\n", mw::join(a_line));
              }

              ++imgNo;
          }
          else
          {
              if (verbose)
              {
                fmt::print(" not an image.\n",  img_ptr->magick());
              }
          }
      } //  for (size_t j = 0; j < found_files.size(); ++j)
    } // for (size_t i = 0; i < all_paths.size(); ++i)



    fmt::print("\n");
    fmt::print("Found {} images out of {} files analyzed\n", imgNo, totalPathNo);
    fmt::print("CSV file saved in: {}\n", out_csv);

    return 0;
}
