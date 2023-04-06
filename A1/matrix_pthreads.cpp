#include <iostream>
#include <fstream>
#include <bits/stdc++.h> 
#include <thread>

using namespace std;

struct Matrix {
    int coloumns = 0;
    int rows = 0;
    float **data;

    Matrix() {};
    Matrix(int r, int c) {
        coloumns = c;
        rows = r;						// new structure Matrix
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
			ans.data[row][j] += m1.data[row][i] * m2.data[i][j];	//Matrix multiplication of single row which can be made run in parallel to threads
		}
	}
}


Matrix MultiplyMatrices(Matrix m1, Matrix m2) {
	Matrix matrix;       
	vector<thread> threads;            
        matrix = Matrix(m1.rows, m2.coloumns);            
        for (int i = 0; i < m1.rows; ++i){					// parallel program using threads parallel row operations
                threads.emplace_back(MultiplyRow, m1, m2, matrix, i);
	}
        for (int i = 0; i < threads.size(); i++){
                threads[i].join();
        }
        return matrix;
}

void AddRow(Matrix m1,Matrix m2, Matrix ans,int row){
	for(int j=0;j < m1.coloumns;j++){
		ans.data[row][j]=m1.data[row][j]+m2.data[row][j];		//Matrix Addition of single row which can be made run in parallel to threads.
	}
}

Matrix AdditionMatrices(Matrix m1,Matrix m2){
	Matrix matrix;
	vector<thread> threads;
	matrix = Matrix(m1.rows,m1.coloumns);
	for(int i=0; i< m1.rows;i++){
		threads.emplace_back(AddRow,m1,m2,matrix,i);			//parallel program using parallel row operations for addition
	}
	for(int i=0 ; i<threads.size();i++){
		threads[i].join();
	}
	return matrix;
}


void matrix_pthreads(string f1,string f2,string f3,string f4)
{
    	fstream file1(f1, fstream::in);
	Matrix matrix1;          
	int n;
	int m;									//pthreads_matrix function
	file1 >> m;
	file1 >> n;								//file reading of matrices in coloumn proyority format
	matrix1 = Matrix(n, m);
	for (int j = 0; j < matrix1.coloumns; j++){ 
                for (int i = 0; i < matrix1.rows; i++){ 
                    file1 >> matrix1.data[i][j];                
            	}
        }
        file1.close();
        fstream file2(f2, fstream::in);
	Matrix matrix2;          
	int a;
	int b;
	file2 >> b;
	file2 >> a;
	matrix2 = Matrix(a, b);
	for (int j = 0; j < matrix2.coloumns; j++){ 
                for (int i = 0; i < matrix2.rows; i++){ 
                    file2 >> matrix2.data[i][j];                
            	}
        }
        file2.close();
        fstream file3(f3, fstream::in);
	Matrix matrix3;          
	int c;
	int d;
	file3 >> d;
	file3 >> c;
	matrix3 = Matrix(c, d);
	for (int j = 0; j < matrix3.coloumns; j++){ 
                for (int i = 0; i < matrix3.rows; i++){ 
                    file3 >> matrix3.data[i][j];                
            	}
        }
        file3.close();
        
    	Matrix result1 = MultiplyMatrices(matrix1, matrix2);			// use thread operations (parallel program)
   	Matrix result = AdditionMatrices(result1,matrix3);
   	
   	ofstream file(f4);
	file << result.coloumns << "\n";
	file << result.rows << "\n";
	for (int j = 0; j < result.coloumns; j++) {
		for (int i = 0; i < result.rows; i++) {			// file output matrix in row proyority format
			file << result.data[i][j] << "\n";
               }
        }
        file.close();	
}
