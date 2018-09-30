#ifndef MYLAB1_MATRIX_H
#define MYLAB1_MATRIX_H

#include <iostream>

using std::ostream;

class Matrix {

	int* matrix;
	int rows;
	int columns;

public:
	Matrix(int, int);

	~Matrix();

	int getRowsNumber();

	int getColumnsNumber();

	int get(int, int);

	void set(int, int, int);

	void initRandom();

	friend ostream& operator<<(ostream& os, const Matrix& dt);

	//Matrix operator=(const Matrix& matrix);

};

#endif