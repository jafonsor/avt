#ifndef _SPHERE_CAMERA_H_
#define _SPHERE_CAMERA_H_

#include "Camera.h"

class SphereCam : public Camera {
	float _xAngle;
	float _yAngle;

private:
	void updateEye();

public:
	SphereCam(Matrix &projection);
	void rotate(float deltaAngleX, float deltaAngleY);
};

#endif