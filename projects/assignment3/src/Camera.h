#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Matrix.h"
#include "Quaternion.h"

class Camera {
	Matrix _projection;

protected:
	Matrix _viewMatrix;
	Vector _eye;
	Vector _center;
	Vector _up;

public:
	Camera(Matrix &projection);
	Matrix getView();
	Matrix getProjection();
	void setProjection(Matrix &projection);
	void lookAt(Vector &eye, Vector &center, Vector &up);
};

#endif