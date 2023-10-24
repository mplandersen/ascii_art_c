# ASCII ART in C
#### Video Demo:  <URL https://youtu.be/vfQHr3_HJlI?si=9DztQ0-Hw-c85Hym>
#### Description:
Modified version of PSET4 adding a new feature which allows users to convert bmp files to ASCII art. Written in C.


The very first project I began was a chrome extension that tracks time spent on a website. Due to the limited amount of learning resources on the recently updated Manifest V3 and its integration of service workers over background pages caused a lot of disruption. After many hours I decided to go to C and do some ASCII art instead. The chrome extension does however have a function that removes google sponsored results from searches.

For the ASCII art project I added -a as a viable option to input for the filter. This caused several issues primarily due to the 'make filter' command not working properly on my local device despite it saying it was up to date. I ended up having to copy paste the clang command from the makefile to update and run the program. I removed lines 63 to 72 so that all bmp files could be used however this was more for curiosities sake and doesn't really work as there is a limit to the amount of characters on a line in notepad. Under the switch (filter) I added the case 'a' and the ascii function. Because the ascii function creates the bmp file I close the inptr and outptr before returning instead of simply breaking like the others.

I added void ascii() to helpers.h and wrote the function in helpers.c. I decided to use the function for greyscaling to render the ASCII image, this is because the ascii image is itself black and white and so would be better suited.

I found a range of ascii symbols in matter of density. I used a python file to apply list to the string symbol chopping them into a list. I later tried to reverse the density to see the effect but didn't enjoy the outcome. I then created the 2D array of char to place each ascii symbol into. 

Two for loops iterate over each pixel as such in the greyscale. The average is taken from the greyscale image and placed into this function: n = (68 * average)/255. the 68 is the amount of ascii items and 255 is the maximum value that average can be. This function divides the average into the 68 respective slots. For more clarity the ascii array could include 256 densities instead perhaps. The new 2D char array then has the symbol placed into it that corresponds to ascii[n]. 

To prevent the function being written on one line I added the newline variable "\n" and when writing the output.txt file I made sure to add it at the end of each width.

I had to reverse the height when writing the 2D array because for some reason the outcome was mirrored or on its head.

How to run:

./filter -a FILENAME.bmp OUTPUT.bmp

*the output bmp does not matter, the ascii will appear as output.txt
*the smaller the bmp file the better


Future features:
Reduce file size automatically to something smaller and so it can fit on a notepad
Different file formats