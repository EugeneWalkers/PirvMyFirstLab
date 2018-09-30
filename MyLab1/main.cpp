#include <iostream>
#include <fstream>
#include "omp.h"
#include "matrix.h"
#include <ctime>

using std::cin;
using std::cout;
using std::ends;
using std::endl;
using std::ofstream;

//int* getRandomMatrix(int, int);
//void printMatrix(int*, int, int);
//int* simpleMultiplication(int*, int*, int, int, int);

Matrix simpleMultiplication(Matrix, Matrix);
Matrix blockMultiplication(Matrix, Matrix, int);


int main(int argc, char* argv) {


	int n1, n2, n3;
	int blockSize;
	int numberOfThreads = 4;

	//cin >> n1 >> n2 >> n3;
	//cin >> blockSize;
	n1 = 500;
	n2 = 500;
	n3 = 750;
	blockSize = 8;
	

	Matrix m1(n1, n2);
	Matrix m2(n2, n3);

	m1.initRandom();
	m2.initRandom();

	omp_set_dynamic(false);
	omp_set_num_threads(numberOfThreads);

	long start = clock();

	Matrix m3 = simpleMultiplication(m1, m2);
	//Matrix m3 = blockMultiplication(m1, m2, blockSize);

	long finish = clock();
	double difference = (finish - start)/1000.0;

	ofstream fin("output.txt", ofstream::out | ofstream::app);
	fin << n1 << ":" << n2 << ":" << n3 << ":" << blockSize << ":" << numberOfThreads << ":" << difference << "\n";
	fin.close();
	
	//cout << m3 << endl;

	return 0;
}

Matrix simpleMultiplication(Matrix matrix1, Matrix matrix2) {
	int rows1 = matrix1.getRowsNumber();
	int columns1 = matrix1.getColumnsNumber();
	int columns2 = matrix2.getColumnsNumber();
	Matrix result (rows1, columns2);

#pragma omp parallel for
	for (int i = 0; i < rows1; i++) {
#pragma omp parallel for
		for (int j = 0; j < columns1; j++) {
#pragma omp parallel for
			for (int k = 0; k < columns2; k++) {
				int a = result.get(i, k);
				int b = matrix1.get(i, j);
				int c = matrix2.get(j, k);
				result.set(i, k, a + b*c);
			}
		}
	}
	return result;
}

Matrix blockMultiplication(Matrix matrix1, Matrix matrix2, int blockSize) {

	int n1 = matrix1.getRowsNumber();
	int n2 = matrix1.getColumnsNumber();
	int n3 = matrix2.getColumnsNumber();
	int q1 = n1 / blockSize;
	int q2 = n2 / blockSize;
	int q3 = n3 / blockSize;

	//cout << n1 << ":" << n2 << ":" << n3 << ":" << q1 << ":" << q2 << ":" << q3 << endl;

	Matrix result(n1, n3);

#pragma omp parallel for
	for (int i1 = 0; i1 < q1; i1++) {
#pragma omp parallel for
		for (int j1 = 0; j1 < q2; j1++) {
#pragma omp parallel for
			for (int k1 = 0; k1 < q3; k1++) {
#pragma omp parallel for
				for (int i2 = 0; i2 < blockSize; i2++) {
#pragma omp parallel for
					for (int j2 = 0; j2 < blockSize; j2++) {
#pragma omp parallel for
						for (int k2 = 0; k2 < blockSize; k2++) {
							int i = i1 * blockSize + i2;
							int j = j1 * blockSize + j2;
							int k = k1 * blockSize + k2;

							int m1value = matrix1.get(i, j);
							int m2value = matrix2.get(j, k);
							int resultvalue = result.get(i, k);

							//cout << i << ":" << j << ":" << k << endl;

							result.set(i, k, resultvalue + m1value*m2value);
						}
					}
				}
			}
		}
	}
	return result;
}