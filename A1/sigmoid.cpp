#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;

void sigmoid(string f1,string f2){		//sigmoid function takes input vectors from file f1 and outputs to file f2
	int n;
	string file1(f1);
	ifstream infile(file1);
	infile>>n;
	float S[n];				//input vector S array representation 
	for(int i=0;i<n;i++){
		infile>>S[i];
	}
	infile.close();
	float A[n];
	for(int i=0;i<n;i++){
		A[i]=1/(1+exp(-S[i]));		// output vector A
	}					//A[i][j]=1/(1+exp(-s[i]))
	ofstream Myfile(f2);
	Myfile<<n<<"\n";
	for(int i=0;i<n;i++){
		Myfile<<A[i]<<"\n";		//outputs to file f2 (prints A to f2)
	}
	Myfile.close();	
}
