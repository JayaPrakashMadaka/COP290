#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "matrix_mkl.cpp"
#include "matrix_openblas.cpp"
#include "matrix_pthreads.cpp"
using namespace std;
using namespace std::chrono;


int main(int argc,char* argv[]){
	  auto start = high_resolution_clock::now();
	if(strcmp(argv[1],"fullyconnected")==0){				// source code reads input from command line
		if(strcmp(argv[2],"mkl")==0){
			matrix_mkl(argv[3],argv[4],argv[5],argv[6]);
		}
		else if(strcmp(argv[2],"openblas")==0){
			matrix_openblas(argv[3],argv[4],argv[5],argv[6]);
		}
		else if(strcmp(argv[2],"pthreads")==0){
			matrix_pthreads(argv[3],argv[4],argv[5],argv[6]);
		}
		else{
			cout << "Error in command";
		}
	}
	else{
		cout << "Error in command";
	}
	
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
 
    cout << "Time taken by function: "
         << duration.count() << " milliseconds" << endl;
 
    return 0;
}
