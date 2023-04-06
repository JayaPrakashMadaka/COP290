#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;

void subsampling_avg(string f1,string f2,int x){		//subsamping_avg function takes input from f1 and a stride x and outputs to f2
	int n;
	int m;
	string file1(f1);
	ifstream infile(file1);
	infile>>m;
	infile>>n;
	float S[n][n];
	for(int j=0;j<n;j++){
		for(int i=0;i<n;i++){				//input matrix S taken from file f1
			infile>>S[i][j];
		}
	}
	infile.close();
	m=n/x;							// m is updated to dimensions of output matrix using stride x
	float	A[m][m];
	for(int i=0;i<m;i++){					// output square matrix A with dimensions m*m
		for(int j=0;j<m;j++){
			A[i][j]=0;
		}
	}
	int a=0;
	while(a<n){
		int b=0;
		while(b<n){
			float sum=0;				//sum is the sum of entris of square matrix x*x starting from pointers a,b
			for(int i=a;i<a+x;i++){
				for(int j=b;j<b+x;j++){
					sum+=S[i][j];
				}
			}
			sum=sum/(x*x);				//sum is ubdated to average by dividing with x^2
			A[a/x][b/x]=sum;
			b+=x;
		}
		a+=x;
	}
	ofstream Myfile(f2);
	Myfile<<m<<"\n";
	Myfile<<m<<"\n";					//output matrix A is printed to file f2
	for(int j=0;j<m;j++){
		for(int i=0;i<m;i++){
			Myfile<<A[i][j]<<"\n";
		}
	}
	Myfile.close();
}
