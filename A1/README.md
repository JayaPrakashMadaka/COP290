# Audio-Processing-Library
Audio Processing Library
This Task contains creation of an audio library audiolib.so 
This directory also contains mfcc_features folder which has different sound signal matrices 1*250


There is a Make file available :

The make commands are:

make : compiles all the files and also libraries created and sets the path along with them/

make clean : removes yourcode.out file

and then type:

./yourcode.out filename.txt out.txt

here filename.txt is the file name of input samples :

eg :- mfcc_features/ca4d5368_nohash_5.txt along with the path of directory if they are in separate folders.

the program outputs the 3 top most probabilities and their respective sounds.

it appends result generated to the file out.txt
