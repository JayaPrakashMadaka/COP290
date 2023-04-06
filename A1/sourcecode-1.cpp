#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "matrix.cpp"
#include "relu.cpp"
#include "tanh.cpp"
#include "subsampling_max.cpp"
#include "subsampling_avg.cpp"
#include "softmax.cpp"
#include "sigmoid.cpp"
using namespace std;

int main(int argc,char* argv[]){				// source code reads input from command line
	if(strcmp(argv[1],"activation")==0){
		if(strcmp(argv[2],"relu")==0){		// based on inputs in command line the function moves to required function
			 relu(argv[3],argv[4]);
		}
		else if(strcmp(argv[2],"tanh")==0){		// all the files which are created matrix,relu,tanh,.... etc are included in this file
			 tanh(argv[3],argv[4]);
		}
	}
	else if (strcmp(argv[1],"fullyconnected")==0){
		matrix(argv[2],argv[3],argv[4],argv[5]);
	}
	else if (strcmp(argv[1],"pooling")==0){
		if(strcmp(argv[2],"max")==0){
			stringstream f(argv[4]);
			int x=0;
			f>>x;
			//int x=stoi(argv[4]);			// sstream inbulit function which convers string to int for stride
			subsampling_max(argv[3],argv[5],x);
		}
		else if(strcmp(argv[2],"average")==0){
			stringstream f(argv[4]);
			int x=0;
			f>>x;			
			//int x=stoi(argv[4]);
			subsampling_avg(argv[3],argv[5],x);
		}
	}
	else if (strcmp(argv[1],"probability")==0){
		if(strcmp(argv[2],"softmax")==0){
			softmax(argv[3],argv[4]);
		}
		else if(strcmp(argv[2],"sigmoid")==0){
			sigmoid(argv[3],argv[4]);
		}
	}
	else{
		cout<<"Error in command line"<<"\n";
	}
	
}
