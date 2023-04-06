#include <iostream>
#include <fstream>
#include <bits/stdc++.h> 
#include <thread>
#include"dnn_weights.h"
#include"libaudio.h"
using namespace std;


struct Matrix {
    int coloumns = 0;
    int rows = 0;
    float **data;

    Matrix() {};
    Matrix(int r, int c) {
        coloumns = c;
        rows = r;
        data = new float* [rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new float[coloumns];
            for (int j = 0; j < coloumns; j++) 
                data[i][j] = 0;            
        }
    }
};

void MultiplyRow(Matrix m1, Matrix m2, Matrix ans, int row) {    
	for (int j = 0; j < m2.coloumns; j++){
		for (int i = 0; i < m1.coloumns; i++){ 
			ans.data[row][j] += m1.data[row][i] * m2.data[i][j];
		}
	}
}


Matrix MultiplyMatrices(Matrix m1, Matrix m2) {
	Matrix matrix;       
	vector<thread> threads;            
        matrix = Matrix(m1.rows, m2.coloumns);            
        for (int i = 0; i < m1.rows; ++i){
                threads.emplace_back(MultiplyRow, m1, m2, matrix, i);
	}
        for (int i = 0; i < threads.size(); i++){
                threads[i].join();
        }
        return matrix;
}

void AddRow(Matrix m1,Matrix m2, Matrix ans,int row){
	for(int j=0;j < m1.coloumns;j++){
		ans.data[row][j]=m1.data[row][j]+m2.data[row][j];
	}
}

Matrix AdditionMatrices(Matrix m1,Matrix m2){
	Matrix matrix;
	vector<thread> threads;
	matrix = Matrix(m1.rows,m1.coloumns);
	for(int i=0; i< m1.rows;i++){
		threads.emplace_back(AddRow,m1,m2,matrix,i);
	}
	for(int i=0 ; i<threads.size();i++){
		threads[i].join();
	}
	return matrix;
}

void reluRow(Matrix m1, Matrix ans , int row){
	for(int j=0; j<m1.coloumns;j++){
		if(m1.data[row][j] > 0 ){
			ans.data[row][j]=m1.data[row][j];
		}
		else{
			ans.data[row][j]=0;
		}
	}
}

Matrix reluall(Matrix m1){
	Matrix matrix;
	vector<thread> threads;
	matrix = Matrix(m1.rows, m1.coloumns);
	for (int i = 0; i < m1.rows; ++i){
                threads.emplace_back(reluRow, m1, matrix, i);
	}
	for(int i=0 ; i<threads.size();i++){
		threads[i].join();
	}
	return matrix;
}


Matrix FC(Matrix m1 , Matrix m2 , Matrix m3)
{
        
    	Matrix result1 = MultiplyMatrices(m1, m2);
   	Matrix result = AdditionMatrices(result1,m3);
   	
   	return result;
}


Matrix relu(Matrix m1){		//relu function which takes input from f1 and prints to f2
	
	Matrix result = reluall(m1);
	return result;
}

Matrix softmax(Matrix m1){

	float sum=0;
	for(int i=0;i<m1.coloumns;i++){
		sum+=exp(m1.data[0][i]);
	}
	Matrix result;
	result = Matrix(m1.rows,m1.coloumns);				//out put vector A A[i][j]=softmax_function(S[i][j])
	for(int i=0;i<m1.coloumns;i++){
		result.data[0][i]=exp(m1.data[0][i])/sum;
	}
	return result;
}

template<typename T>
void BubbleSort(T arr[], int n){
	for(int i=0;i<n-1;++i){
		for(int j=0;j<n-i-1;++j){
			if(arr[j]>arr[j+1]){
				T temp = arr[j+1];
				arr[j+1] = arr[j];
				arr[j] = temp;
			}
		}
	}
}


int search(float arr[],float x,int n){
	for(int i=0;i<n;i++){
		if(arr[i]==x){
			return i;
		}
	}
	return 0;
}

pred_t* libaudioAPI(const char* audiofeatures, pred_t* pred){

	string filename(audiofeatures);    
	vector<float> input;				//inputmatrix(A*B)
        float number;
							//using vectors to take input for input matrix in a while loop
        ifstream in_file(filename);

        while (in_file >> number) {
		input.push_back(number);
    	}

    	in_file.close();
    	
    	
    	
    	Matrix IM;
    	IM = Matrix(1,250);
    	for(int i=0;i<250;i++){
    		IM.data[0][i]=input[i];
    	}
    	float arr1[]=IP1_WT;
    	Matrix WM1;
    	WM1 = Matrix(250,144);
    	int k1=0;
    	for(int i=0;i<250;i++){
    		for(int j=0;j<144;j++){
    			WM1.data[i][j]=arr1[k1];
    			k1++;
    		}
    	}
    	float arr2[]=IP1_BIAS;

    	Matrix BIAS1;
    	BIAS1 = Matrix(1,144);
    	int k2=0;
    	for(int i=0;i<1;i++){
    		for(int j=0;j<144;j++){
    			BIAS1.data[i][j]=arr2[k2];
    			k2++;
    		}
    	}
    	
    	float arr3[] = IP2_WT;
    	Matrix WM2;
    	WM2 = Matrix(144,144);
    	int k3=0;
    	for(int i=0;i<144;i++){
    		for(int j=0;j<144;j++){
    			WM2.data[i][j]=arr3[k3];
    			k3++;
    		}
    	}
    	float arr4[]=IP2_BIAS;
    	Matrix BIAS2;
    	BIAS2 = Matrix(1,144);
    	int k4=0;
    	for(int i=0;i<1;i++){
    		for(int j=0;j<144;j++){
    			BIAS2.data[i][j]=arr4[k4];
    			k4++;
    		}
    	}
    	float arr5[]=IP3_WT;
    	Matrix WM3;
    	WM3 = Matrix(144,144);
    	int k5=0;
    	for(int i=0;i<144;i++){
    		for(int j=0;j<144;j++){
    			WM3.data[i][j]=arr5[k5];
    			k5++;
    		}
    	}
    	float arr6[]=IP3_BIAS;
    	Matrix BIAS3;
    	BIAS3 = Matrix(1,144);
    	int k6=0;
    	for(int i=0;i<1;i++){
    		for(int j=0;j<144;j++){
    			BIAS3.data[i][j]=arr6[k6];
    			k6++;
    		}
    	}
    	float arr7[]=IP4_WT;
    	Matrix WM4;
    	WM4 = Matrix(144,12);
    	int k7=0;
    	for(int i=0;i<144;i++){
    		for(int j=0;j<12;j++){
    			WM4.data[i][j]=arr7[k7];
    			k7++;
    		}
    	}
    	float arr8[]=IP4_BIAS;
    	Matrix BIAS4;
    	BIAS4 = Matrix(1,12);
    	int k8=0;
    	for(int i=0;i<1;i++){
    		for(int j=0;j<12;j++){
    			BIAS4.data[i][j]=arr8[k8];
    			k8++;
    		}
    	}
    	
    	Matrix result1;
    	result1 = Matrix(1,144);
    	result1 = FC(IM,WM1,BIAS1);
    	Matrix result2;
    	result2= Matrix(1,144);
    	result2=relu(result1);
    	Matrix result3;
    	result3 = Matrix(1,144);
    	result3 = FC(result2,WM2,BIAS2);
    	Matrix result4;
    	result4 = Matrix(1,144);
    	result4=relu(result3);
    	Matrix result5=Matrix(1,144);
    	result5=FC(result4,WM3,BIAS3);
    	Matrix result6=Matrix(1,144);
    	result6=relu(result5);
    	Matrix result7 = Matrix(1,12);
    	result7 = FC(result6,WM4,BIAS4);
    	Matrix result8 = Matrix(1,12);
    	result8 = softmax(result7);
    	
    	float arr[12];
    	for(int i=0;i<12;i++){
    		arr[i]=result8.data[0][i];
    	}
    	float ans[12];
    	for(int i=0;i<12;i++){
    		ans[i]=result8.data[0][i];
    	}
	BubbleSort(arr,12);

	int a = search(ans,arr[11],12);
	int  b= search(ans,arr[10],12);
	int  c= search(ans,arr[9],12);
	
	pred_t p1 = {a,arr[11]};
   	pred_t p2 = {b,arr[10]};
    	pred_t p3 = {c,arr[9]};
    	pred_t p[3] = {p1,p2,p3};
    	
    	pred_t *pre = p;
	
	return pre;
}


