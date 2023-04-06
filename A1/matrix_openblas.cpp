#include<cblas.h>
#include <bits/stdc++.h> 
#include <iostream>
#include <fstream>
using namespace std; 

void matrix_openblas(string f1,string f2,string f3,string f4){

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
    	double *A, *B, *C;
 	double alpha, beta;
	alpha = 1.0; beta = 1.0;
 	A = (double *) malloc( n*m*sizeof( double ) );
 	B = (double *) malloc( a*b*sizeof( double ) );
 	C = (double *) malloc( n*b*sizeof( double ) );
 	
 	for(int i=0;i<n;i++){
 		for(int j=0;j<m;j++){
 			A[m*i+j] = IM[i][j];
 		}
 	}
 	for(int i=0;i<a;i++){
 		for(int j=0;j<b;j++){
 			B[b*i+j] = WM[i][j];
 		}
 	}
 	for(int i=0;i<n;i++){
 		for(int j=0;j<b;j++){
 			C[b*i+j] = BM[i][j];
 		}
 	}
 	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,n, b, m, alpha, A, m, B, b, beta, C, b);
 	
 	float ans[n][b];
 	for(int i=0;i<n;i++){
 		for(int j=0;j<b;j++){
 			ans[i][j]=C[b*i+j];
 		}
 	}
 	ofstream Myfile(f4);
	Myfile<<b<<"\n";
	Myfile<<n<<"\n";
	for(int j=0;j<b;j++){					//printing the matrix B coloumn wise priyority to file f2(can be given as input)
		for(int i=0;i<n;i++){
			Myfile<<ans[i][j]<<"\n";
		}
	}
	Myfile.close();	
 }
