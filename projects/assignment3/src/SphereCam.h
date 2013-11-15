#ifndef _SPHERE_CAMERA_H_
#define _SPHERE_CAMERA_H_

#include "Camera.h"

class SphereCam : public Camera {
	float _theta;
	float _phi;
	float _radius;

private:
	void updateEye();

public:
	SphereCam(Matrix &projection, float radius);
	void deltaTheta( float delta);
	void deltaPhi(   float delta);
	void deltaRadius(float delta);
};

#endif