#include "Camera.h"

Matrix Camera::getView() { return _viewMatrix; }

void Camera::lookAt(Vector &eye, Vector &center, Vector &up) {
		Vector view = vSub(center, eye);
		Vector v = vNormalize(view);
		Vector side = vCross(v,up);
		Vector s = vNormalize(side);
		Vector u = vCross(s,v);

		Matrix base;
		base.set(0,0, s.x);
		base.set(0,1, s.y);
		base.set(0,2, s.z);
		base.set(0,3, -s.x*eye.x -s.y*eye.y -s.z*eye.z);

		base.set(1,0, u.x);
		base.set(1,1, u.y);
		base.set(1,2, u.z);
		base.set(1,3, -u.x*eye.x -u.y*eye.y -u.z*eye.z);

		base.set(2,0, -v.x);
		base.set(2,1, -v.y);
		base.set(2,2, -v.z);
		base.set(2,3,  v.x*eye.x +v.y*eye.y +v.z*eye.z);

		base.set(3,3, 1);

		_viewMatrix = base;
}