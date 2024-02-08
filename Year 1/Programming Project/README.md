# Welcome to my Year 1 Programming Project

This may take a bit of explaining...

This project consists of 2 parts, courseworks 1 and 2. The module was based on these 2 courseworks (50-50 split), and tested elements of programming knowledge in C (including the creation and update of the makefile), version control using git and github, elements of bash scripting to create a test bed and complex low level concepts such as compression and bit twiddling to create files used for storing images.

## Background Knowledge

The overall objective across this project was to develop image file conversion, duplication and comparison between custom file types, which is loosely based on the PGM file format.The images themselves are stored using a range of pixel values (0 - 31) to represent black (0), and white (31) into a filetype called an EBF. this file type has its own metadata containing a "magic number", the height and widths of the image, and the image data.

The file type EBU takes the image data from an EBF file, and removes the 1st byte of every number to compress the file by an approximate factor of 1/2. this file type causes the data to become unreadable. The EBU file type has its own magic number, and the height and widths of the image are left untouched.

The file type EBC takes the image data from an EBU file and compresses the image data further. This is how:

- The image data uses only 5 bits inside the 8 bits (or 1 byte) of data stored inside the EBU pixel data, since the max pixel value for the image is 0 - 31
- the EBC file type eliminates these 3 unused bits, and compresses the data such that the pixel values take up 5 bits in the 1st byte, then the next pixel value takes 1st 3 bits in the 1st byte, puts this data together and the next 2 bits go to the next byte
- An example:
    - The pixel values, `30 30 30` are represented as `00011110 00011110 00011110` in the EBU file type
    - The pixel values for this EBU data are compressed so that the 1st byte inside the EBC data type becomes `11110111`, where "11110" is the data of the 1st EBU pixel value. the next value in the EBC type becomes `10111100`, where the 2nd EBU pixel value is the last 3 bits in the 1st EBC byte ("111"), plus the first 2 bits values inside the next EBC byte (10), lastly followed by the next 5 bits inside the 2nd EBC byte (11110), and a trailing 0 to finish the bit off
    - Overall, the pixel values `30 30 30` -> (EBU file) `00011110 00011110 00011110` -> (EBC file) `11110|111 10|11110|0` (| represents the partition in the byte)

I believe on average, the file is losslessly compressed by a factor of 5/8

## Coursework 1

For coursework 1, the objective was to update/create the programs necessary to:
- Create ("Echo") files (3 total, 1 for each file type)
- Compare 2 files to check for similarity for each file type (3 total, 1 for each file type)
- Convert between EBF to EBU, EBU to EBC and vice versa (4 total)

A bash shell test script, simple ebfEcho and ebfComp files and a makefile were provided as a starter ground for development. The objective here was to employ aspects of arrays, reusability, structs, memory management, use of git, and code formatting and comments while also developing the other 8 programs and modifying the test script to accommodate for these other programs.

## Coursework 2

For coursework 2, there were 2 objectives:
1. To improve on coursework 1 from feedback received from the marking team.
2. To develop lossy compression and blocky algorithms between EBC files (explained later)

Part 1 didn't take much effort to do, since I received a good mark and the feedback for that coursework was very positive

Part 2 again, is fairly complicated

### Part 2

For part 2, the objective was to develop the following programs:
- ebcR32 and ebcR128 - blocky programs that take either 32 or 128 random (based on a provided seed) 3x3 pixel blocks from an image, and assigned these blocks to the closely related 3x3 pixel positions and values in an image 
- ebcU32 and ebcU128 - the related unblock algorithms to get from the blocked format to the EBC file format. 
- ebcBlock and ebcUnblock - lossy compression and decompression algorithms that take the EBC file format and 3x3 blocks of pixels inside the image, take the average of the pixels, and save a file with those average pixel values. The compression factor should be around 9 times smaller than an ebc file. The unblock decompresses this file type to the EBC file type  

An object file was provided to convert from the EBF file format to the PGM file format, so that computed images could be looked at and verified to be correct. There are examples inside the `results` folder in the coursework 2 repository, which should be viewable with compatible file viewers either on VSCode, or (on Windows) File Viewer Plus.