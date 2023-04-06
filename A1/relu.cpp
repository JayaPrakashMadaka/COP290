#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;

void relu(string f1,string f2){		//relu function which takes input from f1 and prints to f2
	int n;
	int m;
	string file1(f1);
	ifstream infile(file1);
	infile>>m;
	infile>>n;
	float R[n][m];
	for(int j=0;j<m;j++){			//input matrix R from file f1(2D array representation)
		for(int i=0;i<n;i++){
			infile>>R[i][j];
		}
	}
	infile.close();
	float A[n][m];
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){		//resultant matrix A is initially set to zeros
			A[i][j]=0;
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){		//if the element at location i,j is positive it persists the other is omitted
			if(R[i][j]>0){
				A[i][j]=R[i][j];
			}
		}
	}
	ofstream Myfile(f2);
	Myfile<<m<<"\n";			//printing the resulting matrix to f2
	Myfile<<n<<"\n";
	for(int j=0;j<m;j++){
		for(int i=0;i<n;i++){
			Myfile<<A[i][j]<<"\n";
		}
	}
	Myfile.close();	
}
