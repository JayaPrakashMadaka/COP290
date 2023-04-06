#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void subsampling_max(string f1,string f2,int x){		//subsampling_max function takes input from f1 and stride x from command line and prints to f2
	int n;
	int m;
	string file1(f1);
	ifstream infile(file1);
	infile>>m;
	infile>>n;
	float S[n][n];						//input matrix S
	for(int j=0;j<n;j++){
		for(int i=0;i<n;i++){
			infile>>S[i][j];
		}
	}
	infile.close();
	m=n/x;							// updating m to required square matrix of size m*m
	float	A[m][m];
	for(int i=0;i<m;i++){
		for(int j=0;j<m;j++){
			A[i][j]=0;				//final result matrix A initially set to zero
		}
	}
	int a=0;
	while(a<n){						// a,b pointers to matrix A
		int b=0;
		while(b<n){
			float max=-1000;			//computes max in the x*x from pointers(a,b) matrix and replaces ar A[a/x][b/x]		
			for(int i=a;i<a+x;i++){
				for(int j=b;j<b+x;j++){
					if(S[i][j]>max){	//max updates if it finds another max 
						max=S[i][j];	// note it is assumed that all the signal values are more than -1000 if you want to edit you can just decrease the max value
					}
				}
			}
			A[a/x][b/x]=max;
			b+=x;
		}
		a+=x;
	}
	ofstream Myfile(f2);
	Myfile<<m<<"\n";
	Myfile<<m<<"\n";					//outputs the matrix A to file f2
	for(int j=0;j<m;j++){
		for(int i=0;i<m;i++){
			Myfile<<A[i][j]<<"\n";
		}
	}
	Myfile.close();
}
