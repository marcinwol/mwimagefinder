# mwimagefinder

mwimagefinder searches for image files in a folder and its subfolders.

Unlike normal find/search programs, mwimagefinder **does not relay on file extensions**. It searches and identify image files based on their internal structure. This is especially important in working with large sets of files without or with incorrect extensions. 

The result of the program is a csv file with found files and their type, disk size in MB, pixel spacing and resulution in DPI.

##Motivation

The program was developed in a response to a growing need of working with large sets of images in a JPEG, TIFF and DICOM formats. 

##Examples
Search for DCM, TIFF and JPEG image files in /media/dir1/ /home/m/dir2/. Save results in ./results.csv.
```bash
mwimagefinder --in-dir /media/dir1/ /home/m/dir2/ --csv-file ./results.csv --file-type DCM,TIFF,JPEG 
```


