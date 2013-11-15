#include "SphereCam.h"
#include <cmath>

SphereCam::SphereCam(Matrix &projection, float radius) :
   Camera(projection), _theta(0), _phi(0), _radius(radius)
{
	// empty
}

void SphereCam::updateEye() {
	Vector eye = {
		_radius * cos(_theta),
		_radius * sin(_theta) * cos(_phi),
		_radius * sin(_theta) * sin(_phi)
	};
	lookAt(eye, _center, _up);
}

void SphereCam::deltaTheta(float delta) {
	_theta += delta;
	updateEye();
}

void SphereCam::deltaPhi(float delta) {
	_phi += delta;
	updateEye();
}

void SphereCam::deltaRadius(float delta) {
	_radius += delta;
	updateEye();
}