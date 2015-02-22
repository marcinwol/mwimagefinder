# mwimagefinder

mwimagefinder searches for image files in a folder and its subfolders.

Unlike normal find/search programs, mwimagefinder **does not relay on file extensions**. It searches and identify image files based on their internal structure. This is especially important in working with large sets of files without or with incorrect extensions. 

The result of the program is a csv file with found files and their type, disk size in MB, pixel spacing and resulution in DPI.

##Motivation

The program was developed in a response to a growing need of working with large sets of images in a JPEG, TIFF and DICOM formats. 

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
```
mwimagefinder --file-type JPEG,PNG --csv-file  /tmp/found_JPEG.csv --in-dir /tmp/
```


Search for all image files in /media/dir1/ /home/m/dir2/. Save results in /tmp/results.csv:
```
mwimagefinder --in-dir /media/dir1/ /home/m/dir2/ --csv-file /tmp/results.csv
```

Search for DCM, TIFF and JPEG image files in /media/dir1/ /home/m/dir2/. Save results in ./results.csv:
```
mwimagefinder --in-dir /media/dir1/ /home/m/dir2/ --csv-file ./results.csv --file-type DCM,TIFF,JPEG 
```


