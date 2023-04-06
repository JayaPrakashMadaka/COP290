#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;

void tanh(string f1,string f2){
	int n;
	int m;
	string file1(f1);
	ifstream infile(file1);
	infile>>m;
	infile>>n;
	float T[n][m];
	for(int j=0;j<m;j++){
		for(int i=0;i<n;i++){
			infile>>T[i][j];
		}
	}
	infile.close();
	float A[n][m];
	
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			A[i][j]=0;
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
				A[i][j]=tanh(T[i][j]);
			}
		}
	ofstream Myfile(f2);
	Myfile<<m<<"\n";
	Myfile<<n<<"\n";
	for(int j=0;j<m;j++){
		for(int i=0;i<n;i++){
			Myfile<<A[i][j]<<"\n";
		}
	}
	Myfile.close();	
}
