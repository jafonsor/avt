#include "Quaternion.h"

#include <iostream>
#include <string>
#include <cmath>

#define DEGREES_TO_RADIANS 0.01745329251994329547
#define RADIANS_TO_DEGREES 57.29577951308232185913

const Vector vNormalize(const Vector& v) 
{
	Vector vn;
	float s = 1 / sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
	vn.x = v.x * s;
	vn.y = v.y * s;
	vn.z = v.z * s;
	vn.w = v.w * s;
	return vn;
}

const void vPrint(const std::string s, const Vector& v) 
{
	std::cout << s << " = (" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")" << std::endl;
}

const bool vEqual(const Vector& v0, const Vector& v1)
{
	return ( fabs(v0.x-v1.x) < vThreshold && fabs(v0.y-v1.y) < vThreshold &&
		     fabs(v0.z-v1.z) < vThreshold && fabs(v0.w-v1.w) < vThreshold );
}

const Vector vCross(const Vector& v0,    const Vector& v1) {
	Vector v;
	v.x = v0.y * v1.z  -  v0.z * v1.y;
	v.y = v0.z * v1.x  -  v0.x * v1.z;
	v.z = v0.x * v1.y  -  v0.y * v1.x;
	v.w = 0;
	return v;
}


const Vector vSub(const Vector& v0, const Vector& v1) {
	Vector v;
	v.x = v0.x - v1.x;
	v.y = v0.y - v1.y;
	v.z = v0.z - v1.z;
	v.w = 0;
	return v;
}


const float mThreshold = (float)1.0e-5;

const void mClean(float m[16])
{
	for(int i = 0; i < 16; i++){
		if(fabs(m[i]) < mThreshold) m[i] = 0.0f;
	}
}

const Quaternion qFromAngleAxis(float theta, Vector axis)
{
	Vector axisn = vNormalize(axis);

	Quaternion q;
	float a = theta * (float)DEGREES_TO_RADIANS;
	q.t = cos(a / 2.0f);
	float s = sin(a / 2.0f);
	q.x = axisn.x * s;
	q.y = axisn.y * s;
	q.z = axisn.z * s;

	qClean(q);
	return qNormalize(q);
	//return q;
}

const void qToAngleAxis(const Quaternion& q, float& theta, Vector& axis)
{
	Quaternion qn = qNormalize(q);
	theta = 2.0f * acos(qn.t) * (float)RADIANS_TO_DEGREES;
	float s = sqrt(1.0f - qn.t*qn.t);
	if(s < qThreshold) {
		axis.x = 1.0f;
		axis.y = 0.0f;
		axis.z = 0.0f;
		axis.w = 1.0f;
	} else {
		axis.x = qn.x / s;
		axis.y = qn.y / s;
		axis.z = qn.z / s;
		axis.w = 1.0f;
	}
}

const void qClean(Quaternion& q)
{
	if(fabs(q.t) < qThreshold) q.t = 0.0f;
	if(fabs(q.x) < qThreshold) q.x = 0.0f;
	if(fabs(q.y) < qThreshold) q.y = 0.0f;
	if(fabs(q.z) < qThreshold) q.z = 0.0f;
}

const float qQuadrance(const Quaternion& q)
{
	return q.t*q.t + q.x*q.x + q.y*q.y + q.z*q.z;
}

const float qNorm(const Quaternion& q)
{
	return sqrt(qQuadrance(q));
}

const Quaternion qNormalize(const Quaternion& q)
{
	float s = 1 / qNorm(q);
	return qMultiply(q, s);
}

const Quaternion qConjugate(const Quaternion& q)
{
	Quaternion qconj = { q.t, -q.x, -q.y, -q.z };
	return qconj;
}

const Quaternion qInverse(const Quaternion& q)
{
	return qMultiply(qConjugate(q), 1.0f / qQuadrance(q));
}

const Quaternion qAdd(const Quaternion& q0, const Quaternion& q1)
{
	Quaternion q;
	q.t = q0.t + q1.t;
	q.x = q0.x + q1.x;
	q.y = q0.y + q1.y;
	q.z = q0.z + q1.z;
	return q;
}

const Quaternion qMultiply(const Quaternion& q, const float s)
{
	Quaternion sq;
	sq.t = s * q.t;
	sq.x = s * q.x;
	sq.y = s * q.y;
	sq.z = s * q.z;
	return sq;
}

const Quaternion qMultiply(const Quaternion& q0, const Quaternion& q1)
{
	Quaternion q;
	q.t = q0.t * q1.t - q0.x * q1.x - q0.y * q1.y - q0.z * q1.z;
	q.x = q0.t * q1.x + q0.x * q1.t + q0.y * q1.z - q0.z * q1.y;
	q.y = q0.t * q1.y + q0.y * q1.t + q0.z * q1.x - q0.x * q1.z;
	q.z = q0.t * q1.z + q0.z * q1.t + q0.x * q1.y - q0.y * q1.x;
	return q;
}

const void qGLMatrix(const Quaternion& q, float matrix[16]) {
	Quaternion qn = qNormalize(q);

	float xx = qn.x * qn.x;
	float xy = qn.x * qn.y;
	float xz = qn.x * qn.z;
	float xt = qn.x * qn.t;
	float yy = qn.y * qn.y;
	float yz = qn.y * qn.z;
	float yt = qn.y * qn.t;
	float zz = qn.z * qn.z;
	float zt = qn.z * qn.t;

	matrix[0] = 1.0f - 2.0f * ( yy + zz );
	matrix[1] = 2.0f * ( xy + zt );
	matrix[2] = 2.0f * ( xz - yt );
	matrix[3] = 0.0f;

	matrix[4] = 2.0f * ( xy - zt );
	matrix[5] = 1.0f - 2.0f * ( xx + zz );
	matrix[6] = 2.0f * ( yz + xt );
	matrix[7] = 0.0f;

	matrix[8] = 2.0f * ( xz + yt );
	matrix[9] = 2.0f * ( yz - xt );
	matrix[10] = 1.0f - 2.0f * ( xx + yy );
	matrix[11] = 0.0f;

	matrix[12] = 0.0f;
	matrix[13] = 0.0f;
	matrix[14] = 0.0f;
	matrix[15] = 1.0f;

	mClean(matrix);
}

const Quaternion qLerp(const Quaternion& q0, const Quaternion& q1, float k)
{
	float cos_angle = q0.x*q1.x + q0.y*q1.y + q0.z*q1.z + q0.t*q1.t;
	float k0 = 1.0f - k;
	float k1 = (cos_angle > 0) ? k : -k;
	return qAdd(qMultiply(q0,k0), qMultiply(q1,k1));
}

const Quaternion qSlerp(const Quaternion& q0, const Quaternion& q1, float k) 
{
	float angle = acos(q0.x*q1.x + q0.y*q1.y + q0.z*q1.z + q0.t*q1.t);
	float k0 = sin((1-k)*angle) / sin(angle);
	float k1 = sin(k*angle) / sin(angle);
	return qAdd(qMultiply(q0,k0), qMultiply(q1,k1));
}

const bool qEqual(const Quaternion& q0, const Quaternion& q1)
{
	return ( fabs(q0.t-q1.t) < qThreshold && fabs(q0.x-q1.x) < qThreshold &&
		     fabs(q0.y-q1.y) < qThreshold && fabs(q0.z-q1.z) < qThreshold );
}

const void qPrint(const std::string& s, const Quaternion& q) 
{
	std::cout << s << " = (" << q.t << ", " << q.x << ", " << q.y << ", " << q.z << ")" << std::endl;
}

const void qPrintAngleAxis(const std::string& s, const Quaternion& q)
{
	std::cout << s << " = ";

	float thetaf;
	Vector axis_f; 
	qToAngleAxis(q, thetaf, axis_f);
	std::cout << "angle = " << thetaf << " "; 
	vPrint("axis", axis_f);
}