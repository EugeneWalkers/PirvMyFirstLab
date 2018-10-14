#include "matrix.h"
#include <iostream>


using namespace std;

Matrix::Matrix(int _rows, int _columns) {
	this->rows = _rows;
	this->columns = _columns;
	matrix = new int[rows*columns]();
}

Matrix::~Matrix() {
	/*delete matrix;*/
}

int Matrix::getRowsNumber() {
	return rows;
}

int Matrix::getColumnsNumber() {
	return columns;
}

int Matrix::get(int i, int j) {
	return matrix[i*columns + j];
}

void Matrix::set(int i, int j, int value) {
	matrix[i*columns+ j] = value;
}

void Matrix::initRandom() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			matrix[columns*i + j] = rand() % 200 - 100;
		}
	}


}

//Matrix Matrix::operator=(const Matrix& matrix) {
//	this->columns = matrix.columns;
//	this->rows = matrix.rows;
//	this->matrix = new int[rows*columns]();
//	for (int i = 0; i < rows; i++) {
//		for (int j = 0; j < columns; j++) {
//			this->matrix[i*rows + j] = matrix.matrix[i*rows + j];
//		}
//	}
//	return *this;
//}

ostream& operator<<(ostream& out, const Matrix& matr)
{
	out << "------------------------" << endl;

	for (int i = 0; i < matr.rows; i++) {
		for (int j = 0; j < matr.columns; j++) {
			out << matr.matrix[i*matr.columns+ j] << ends;
		}
		cout << endl;
	}
	out << "------------------------" << endl;
	return out;
}