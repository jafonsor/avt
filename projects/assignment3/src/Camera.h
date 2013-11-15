#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Matrix.h"
#include "Quaternion.h"

class Camera {
	Matrix _viewMatrix;

public:
	Matrix getView();
	void lookAt(Vector &eye, Vector &center, Vector &up);
};

#endif