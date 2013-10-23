#ifndef MATRIX_H
#define MATRIX_H

#include "GL/glew.h"

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

	Matrix& operator+(Matrix &otherMatrix);
	Matrix& operator*(Matrix &otherMatrix);
};

#endif
