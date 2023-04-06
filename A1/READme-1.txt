This Task contains a sourcecode.cpp which class all the functions based on the command lines given 

Functions such as relu,tanh,subsampling_avg,subsampling_max etc,... implemented  on matrix and sigmoid softmax functios implemented on vectors are tested in this programm

It contains a Makefile which combin and compiles all the files

Type make (or) make all  command in the directory where all the files are present.

You need to give a input file .txt format with any name of your wish(eg inputmatrix.txt) and can create a desired output file with specific functions running with specific commands.

on pressing make/make all you will see 

g++ -c -Wall sourcecode.cpp
g++ sourcecode.o -o yourcode.out

on cmd..

and a yourcode.out file in the directory created along with .o files.

now you are expected to follow certain commands to activate certain functions in cmd.

	./yourcode.out fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt outputmatrix.txt
	
	you are expected to give three input files(inputmatrix.txt weightmatrix.txt biasmatrix.txt ) with coloumn prior matrix format 
	and you a file named outputmatrix.txt is created in the directory which has output of function.
	
	./yourcode.out activation relu inputmatrix.txt outputmatrix.txt
	
	you are expected to give input file(inputmatrix.txt ) with coloumn prior matrix format 
	and you a file named outputmatrix.txt is created in the directory which has output of function(relu).
	
	./yourcode.out activation tanh inputmatrix.txt outputmatrix.txt
	
	you are expected to give input file(inputmatrix.txt ) with coloumn prior matrix format 
	and you a file named outputmatrix.txt is created in the directory which has output of function(tanh).
	
	./yourcode.out pooling max inputmatrix.txt stride outputmatrix.txt 
	
	you are expected to give input file(inputmatrix.txt ) and a int multiple of n in square matrix in the place of stride with coloumn prior matrix format 
	and you a file named outputmatrix.txt is created in the directory which has output of function(subsampling_max).
	
	./yourcode.out pooling average inputmatrix.txt stride outputmatrix.txt 
	
	you are expected to give input file(inputmatrix.txt ) and a int multiple of n in square matrix in the place of stride with coloumn prior matrix format 
	and you a file named outputmatrix.txt is created in the directory which has output of function(subsampling_avg).
	
	./yourcode.out probability softmax inputvector.txt outputvector.txt
	
	you are expected to give input file(inputvector.txt )  with coloumn prior matrix format 
	and you a file named outputmatrix.txt is created in the directory which has output of function(softmax).
	
	./yourcode.out probability sigmoid inputvector.txt outputvector.txt
	
	you are expected to give input file(inputvector.txt )  with coloumn prior matrix format 
	and you a file named outputmatrix.txt is created in the directory which has output of function(sigmoid).
	
make clean command will clear all the .o files and yourcode.out file in the directory	
