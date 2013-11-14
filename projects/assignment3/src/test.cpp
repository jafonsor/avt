#include <iostream>

#include "Matrix.h"

void printValues(GLfloat *vals) {
	for(int i = 0; i < 16; i++) {
		std::cout << vals[i] << "; ";
	}
}


int main() {
	printValues(Matrix::createOrtho(-20,20, -20,20, 1,10).getValues());
	return 0;
}
