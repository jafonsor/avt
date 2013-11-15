#ifndef _QUATERNION_H_
#define _QUATERNION_H_

#include <string>

typedef struct {
	float x, y, z, w;
} Vector;

const float vThreshold = (float)1.0e-5;
const Vector vNormalize(const Vector& v);
const void   vPrint(const std::string s, const Vector& v);
const bool   vEqual(const Vector& v0, const Vector& v1);
const Vector vCross(const Vector& v0, const Vector& v1);
const Vector vSub(  const Vector& v0, const Vector& v1);

typedef struct {
	float t, x, y, z;
} Quaternion;

const float qThreshold = (float)1.0e-5;
const Quaternion qFromAngleAxis(float theta, Vector axis);
const void qToAngleAxix(const Quaternion& q, float& theta, Vector& axis);
const void qClean(Quaternion& q);
const float qQuadrance(const Quaternion& q);
const float qNorm(const Quaternion& q);
const Quaternion qNormalize(const Quaternion& q);
const Quaternion qConjugate(const Quaternion& q);
const Quaternion qInverse(const Quaternion& q);
const Quaternion qMultiply(const Quaternion& q, const float s);
const Quaternion qMultiply(const Quaternion& q0, const Quaternion& q1);
const void qGLMatrix(const Quaternion& q, float matrix[16]);
const Quaternion qSlerp(const Quaternion& q0, const Quaternion& q1, float k);
const bool qEqual(const Quaternion& q0, const Quaternion& q1);
const void qPrint(const std::string& s, const Quaternion& q);
const void qPrintAngleAxis(const std::string& s, const Quaternion& q);

#endif