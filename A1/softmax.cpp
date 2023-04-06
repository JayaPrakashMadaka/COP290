#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;

void softmax(string f1,string f2){		//softmax function takes input vector from f1 and outputs to f2
	int n;
	string file1(f1);
	ifstream infile(file1);
	infile>>n;
	float S[n];
	for(int i=0;i<n;i++){			//input vector S
		infile>>S[i];
	}
	infile.close();
	float sum=0;
	for(int i=0;i<n;i++){
		sum+=exp(S[i]);
	}
	float A[n];				//out put vector A A[i][j]=softmax_function(S[i][j])
	for(int i=0;i<n;i++){
		A[i]=exp(S[i])/sum;
	}
	ofstream Myfile(f2);
	Myfile<<n<<"\n";			//A is printed to file f2
	for(int i=0;i<n;i++){
		Myfile<<A[i]<<"\n";
	}
	Myfile.close();	
}
