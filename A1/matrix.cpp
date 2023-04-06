#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;

void matrix(string f1,string f2, string f3, string f4){

	string filename(f1);    
	vector<float> input;				//inputmatrix(A*B)
        float number;
							//using vectors to take input for input matrix in a while loop
        ifstream in_file(filename);

        while (in_file >> number) {
		input.push_back(number);
    	}

    	in_file.close();
    	
    	string filename1(f2);				//using vectors to take input for weight matrix in a while loop
    	vector<float> weight;
    	
    	ifstream  we_file(filename1);
    	while(we_file>>number){
    		weight.push_back(number);		//weightmatrix(B*C)
    	}
    	
    	we_file.close();
    	
    	string filename2(f3);
    	
    	vector<float> bias;
    	
    	ifstream  bi_file(filename2);			//biasmatrix(A*C)
    							//using vectors to take input for bias matrix in a while loop
    	while(bi_file>>number){
    		bias.push_back(number);
    	}
    	
    	bi_file.close();
    	
    	int m=input[0];
    	int n=input[1];
    	int b=weight[0];
    	int a=weight[1];
    	float	IM[n][m];
    	int k1=2;
    	for(int j=0;j<m;j++){				//loading the vector to 2D array (matrix)
    		for(int i=0;i<n;i++){
    			IM[i][j]=input[k1];
    			k1++;
    		}
    	}
    	float WM[a][b];
    	int k2=2;
    	for(int j=0;j<b;j++){
    		for(int i=0;i<a;i++){			//loading the vector to 2D array (matrix)
    			WM[i][j]=weight[k2];
    			k2++;
    		}
    	}
    	float BM[n][b];
    	int k3=2;
    	for(int j=0;j<b;j++){
    		for(int i=0;i<n;i++){			//loading the vector to 2D array (matrix)
    			BM[i][j]=bias[k3];
    			k3++;
    		}
    	}
    	float  A[n][b];
    	for(int i=0;i<n;i++){
		for(int j=0;j<b;j++){			//result matrix is A when multiplication done for IM and WM
			A[i][j]=0;
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<b;j++){
			for(int k=0;k<m;k++){
				A[i][j] += IM[i][k]*WM[k][j];		//multiplication of input matrix and weight matrix O(n^3) time complexity
			}
		}
	}
	
	
	float B[n][b];
	for(int i=0;i<n;i++){
		for(int j=0;j<b;j++){
			B[i][j]=0;
		}							// the final result matrix after addition of bias matrix is B.
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<b;j++){
			B[i][j] = A[i][j]+BM[i][j];		//addition result matrix eith bias matrix O(n^2) time complexity
		}
	}
	ofstream Myfile(f4);
	Myfile<<b<<"\n";
	Myfile<<n<<"\n";
	for(int j=0;j<b;j++){					//printing the matrix B coloumn wise priyority to file f2(can be given as input)
		for(int i=0;i<n;i++){
			Myfile<<B[i][j]<<"\n";
		}
	}
	Myfile.close();
}
