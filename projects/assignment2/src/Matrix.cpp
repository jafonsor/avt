#include "Matrix.h"

#include <cstdlib>
#include <iostream>


void print(Matrix &matrix) {
	for(int c =0; c < 4; c++) {
		for(int l=0; l < 4; l++) {
			std::cout << matrix.get(c,l) << " ";
		}
		std::cout << std::endl;
	}
}

Matrix::Matrix() {
	_values = (GLfloat*)malloc( sizeof(GLfloat) * 16 );
	for(int l=0; l < 4; l++) {
		for(int c = 0; c < 4; c++)
			this->set(l,c, 0); 
	}
}

Matrix::Matrix(GLfloat *values):
	_values(values)
{
	// empty
}

Matrix &Matrix::createIdentity() {
	Matrix *result = new Matrix();
	result->set(0,0, 1);
	result->set(1,1, 1);
	result->set(2,2, 1);
	result->set(3,3, 1);
	return *result;
}

Matrix &Matrix::createTranslation(float dx, float dy, float dz) {
	Matrix &result = Matrix::createIdentity();
	result.set(0,3, dx);
	result.set(1,3, dy);
	result.set(2,3, dz);
	print(result);
	return result;
}
	
void Matrix::set(int x, int y, GLfloat value) {
	_values[4*x + y] = value;
}

GLfloat Matrix::get(int x, int y) {
	return _values[4*x + y];
}

GLfloat *Matrix::getValues() {
	return _values;
}


Matrix& operator+(Matrix &otherMatrix);


Matrix& Matrix::operator+(Matrix &otherMatrix) {
	Matrix *result = new Matrix();
	for(int x = 0; x < 4; x++) {
		for(int y =0; y < 4; y++) {
			result->set(x,y, this->get(x,y) + otherMatrix.get(x,y) );
		}
	}
	return *result;
}

Matrix& Matrix::operator*(Matrix &otherMatrix) {
	Matrix *result = new Matrix();
	for(int x = 0; x < 4; x++) {
		for(int y =0; y < 4; y++) {
			result->set(x,y, 0);
			for(int l = 0; l < 4; l++) {
				result->set(x,y, this->get(x,l) * otherMatrix.get(l,y) + result->get(x,y) );
			}
		}
	}
	return *result;
}

