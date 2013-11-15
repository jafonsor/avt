#include "SphereCam.h"
#include <cmath>

SphereCam::SphereCam(Matrix &projection) :
   Camera(projection), _xAngle(0), _yAngle(0)
{
	// empty
}

void SphereCam::rotate(float deltaAngleX, float deltaAngleY) {
	_xAngle += deltaAngleX;
	_yAngle += deltaAngleY;

	Matrix rotationX = Matrix::createRotationX(_xAngle);
	Matrix rotationY = Matrix::createRotationY(_yAngle);

	lookAt(_eye, _center, _up);
	_viewMatrix  = rotationX * rotationY * _viewMatrix;
}