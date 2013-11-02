#ifndef MATRIX_H
#define MATRIX_H

#include "GL/glew.h"

const float PI = 3.14;

class Matrix {
	GLfloat *_values;
public:
	Matrix();
	Matrix(GLfloat *_values);
	
	void set(int x, int y, GLfloat value);
	GLfloat get(int x, int y);
	GLfloat *getValues();
	
	static Matrix &createIdentity();
	static Matrix &createTranslation(GLfloat dx, GLfloat dy, GLfloat dz);
	static Matrix &createRotationZ(float angle);

	Matrix& operator+(Matrix &otherMatrix);
	Matrix& operator*(Matrix &otherMatrix);
};

void print(Matrix &matrix);

#endif
