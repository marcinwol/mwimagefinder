# mwimagefinder

mwimagefinder searches for image files in a folder (or folders) and their subfolders.

Unlike normal find/search programs, mwimagefinder **does not relay on file extensions**. It searches and identifies image files based on their internal structure. This is especially important in working with large sets of files without or with incorrect extensions. 

The result of the program is a csv file with found files and their type, disk size in MB, pixel spacing and resolution in DPI.

##Motivation

The program was developed in a response to a growing need of working with large sets of images in a JPEG, TIFF and DICOM formats without extensions. Thus, using normal file search methods that rely on file extensions or filenames were rather impossible. 

##Supported formats

mwimagefinder uses [ImageMagick](http://www.imagemagick.org/) for identifying image files, thus it supports all formats supported by ImageMagick. There are over 100 major image formats. For complete list of the files supported see [here](http://www.imagemagick.org/script/formats.php).

Since ImageMagick format support depends on many external libraries (e.g. zlib) the best way to check which formats are support on your system is to use the following command:
```
identify -list format
```

##Example usage

Search for image files in the current folder. Save results in found_files.csv:
```bash
mwimagefinder
```
Search for JPEG files in the current folder and save results in /tmp/found_JPEG.csv:
```bash
mwimagefinder --file-type JPEG --csv-file  /tmp/found_JPEG.csv
```

Search for JPEG and PNG files in the /tmp folder and save results in /tmp/found_JPEG.csv"
```bash
mwimagefinder --file-type JPEG,PNG --csv-file  /tmp/found_JPEG.csv --in-dir /tmp/
```


Search for all image files in /media/dir1/ /home/m/dir2/. Save results in /tmp/results.csv:
```bash
mwimagefinder --in-dir /media/dir1/ /home/m/dir2/ --csv-file /tmp/results.csv
```

Search for DCM, TIFF and JPEG image files in /media/dir1/ /home/m/dir2/. Save results in ./results.csv:
```bash
mwimagefinder --in-dir /media/dir1/ /home/m/dir2/ --csv-file ./results.csv --file-type DCM,TIFF,JPEG 
```

Fast (using only file signature, thus no pixel size nor resolution is detected) search for image files in the two folders:
```bash
mwimagefinder --in-dir /media/dir1/ /home/m/dir2/ -f
```

## Example of csv file created

The csv file shown below was a result of searching JPEG and DCM files in /media/sf_D_DRIVE/ and in "/home/m/dcm_for_tests"

|In_dir|File|Type|Size[MB]|ps_x[mm]|ps_y[mm]|DPIx|DPIy|
|-----|-----|-----|-----|-----|-----|-----|-----|
|"/media/sf_D_DRIVE/"|"/media/sf_D_DRIVE/From_SD_Card/DCIM/Camera/IMG_20131226_155158.jpg"|JPEG|0.430859|0.352778|0.352778|69.165354|69.165354|
|"/home/m/dcm_for_tests"|"/home/m/dcm_for_tests/0000b-no-phi.dcm"|DCM|1.400000|0.143000|0.143000|170.629371|170.629371|
|"/home/m/dcm_for_tests"|"/home/m/dcm_for_tests/0001x-no-phi.dcm"|DCM|0.880000|0.143000|0.143000|170.629371|170.629371|
|"/home/m/dcm_for_tests"|"/home/m/dcm_for_tests/0002x-no-phi.dcm"|DCM|0.220000|0.143000|0.143000|170.629371|170.629371|

## Compilation and installation 

#### Dependencies (Ubuntu 14.04):
```bash
sudo apt-get install build-essential qt5-default libmagick++-dev libboost-filesystem1.55-dev libboost-program-options1.55-dev libboost-regex1.55-dev
```

#### Get the source code
```bash
git clone https://github.com/marcinwol/mwimagefinder.git
cd mwimagefinder
```

#### Create Makefile and compile
```bash
qmake && make
````

#### Install in /opt/mwimagefinder
```bash
qmake && sudo make install
```

