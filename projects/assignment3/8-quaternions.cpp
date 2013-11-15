///////////////////////////////////////////////////////////////////////
//
// Using quaternions to rotate in 3D.
//
// (c) 2013 by Carlos Martinho
//
///////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <cassert>

#define DEGREES_TO_RADIANS 0.01745329251994329547
#define RADIANS_TO_DEGREES 57.29577951308232185913

/////////////////////////////////////////////////////////////////////// VECTOR

typedef struct {
	float x, y, z, w;
} Vector;

const float vThreshold = (float)1.0e-5;
const Vector vNormalize(const Vector& v);
const void vPrint(const std::string s, const Vector& v);
const bool vEqual(const Vector& v0, const Vector& v1);

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

/////////////////////////////////////////////////////////////////////// MATRIX

typedef float Matrix[16];
const float mThreshold = (float)1.0e-5;

const Vector mMultiply(Matrix m, Vector& v)
{
	Vector r;
	r.x = m[0] * v.x + m[4] * v.y + m[8]* v.z + m[12] * v.w; 
	r.y = m[1] * v.x + m[5] * v.y + m[9]* v.z + m[13] * v.w; 
	r.z = m[2] * v.x + m[6] * v.y + m[10]* v.z + m[14] * v.w; 
	r.w = m[3] * v.x + m[7] * v.y + m[11]* v.z + m[15] * v.w; 
	return r;
}

const void mClean(Matrix m)
{
	for(int i = 0; i < 16; i++){
		if(fabs(m[i]) < mThreshold) m[i] = 0.0f;
	}
}

/////////////////////////////////////////////////////////////////////// QUATERNION

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
const void qMatrix(const Quaternion& q, float matrix[16]);
const Quaternion qSlerp(const Quaternion& q0, const Quaternion& q1, float k);
const bool qEqual(const Quaternion& q0, const Quaternion& q1);
const void qPrint(const std::string& s, const Quaternion& q);
const void qPrintAngleAxis(const std::string& s, const Quaternion& q);

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

///////////////////////////////////////////////////////////////////////

#define HEADER(X) std::cout<<std::endl<<(X)<<std::endl<<std::endl;

void qtest1()
{
	HEADER("TEST 1 : Rotation of 90 degrees about the y-axis")

	Vector axis = {0.0f, 1.0f, 0.0f};
	Quaternion q = qFromAngleAxis(90.0f, axis);
	qPrint("   q", q);

	Quaternion vi = {0.0f, 7.0f, 0.0f, 0.0f};
	qPrint("  vi", vi);

	Quaternion ve = {0.0f, 0.0f, 0.0f, -7.0f};
	qPrint("  ve", ve);

	Quaternion qinv = qInverse(q);
	//qClean(qinv);
	qPrint("qinv", qinv);

	Quaternion vf = qMultiply(qMultiply(q,vi), qinv);
	qPrint("  vf", vf);

	assert(qEqual(vf, ve));
}

void qtest2()
{
	HEADER("TEST 2 : Rotation of 90 degrees about the y-axis with matrix")

	Vector axis = {0.0f, 1.0f, 0.0f, 1.0f};
	Quaternion q = qFromAngleAxis(90.0f, axis);
	qPrint(" q", q);

	Vector vi = {7.0f, 0.0f, 0.0f, 1.0f};
	vPrint("vi", vi);

	Vector ve = {0.0f, 0.0f, -7.0f, 1.0f};
	vPrint("ve", ve);

	Matrix m;
	qGLMatrix(q,m);

	Vector vf = mMultiply(m, vi);
	vPrint("vf", vf);

	assert(vEqual(vf, ve));
}

void qtest3()
{
	HEADER("TEST 3 : Yaw 180 = Roll 180 + Pitch 180")

	Vector axis_x = {1.0f, 0.0f, 0.0f, 1.0f};
	Vector axis_y = {0.0f, 1.0f, 0.0f, 1.0f};
	Vector axis_z = {0.0f, 0.0f, 1.0f, 1.0f};

	Quaternion qyaw180 = qFromAngleAxis(900.0f, axis_y); // but not 540.0!
	qPrint("  qyaw180", qyaw180);

	Quaternion qroll180 = qFromAngleAxis(180.0f, axis_x);
	qPrint(" qroll180", qroll180);

	Quaternion qpitch180 = qFromAngleAxis(180.0f, axis_z);
	qPrint("qpitch180", qpitch180);

	Quaternion qtest = qMultiply(qpitch180, qroll180);
	qPrint("    qtest", qtest);

	assert(qEqual(qyaw180, qtest));
}

void qtest4()
{
	HEADER("TEST 4: Q <-> (angle, axis)")

	float thetai = 45.0f;
	Vector axis_i = {0.0f, 1.0f, 0.0f, 1.0f};
	Quaternion q = qFromAngleAxis(thetai, axis_i);
	std::cout << thetai << " "; 
	vPrint("axis_i", axis_i);

	float thetaf;
	Vector axis_f; 
	qToAngleAxis(q, thetaf, axis_f);
	std::cout << thetaf << " "; 
	vPrint("axis_f", axis_f);
	
	assert(fabs(thetai - thetaf) < qThreshold && vEqual(axis_i, axis_f)); 
}

void qtest5()
{
	HEADER("TEST 5: LERP")

	Vector axis = {0.0f, 1.0f, 0.0f, 1.0f};
	Quaternion q0 = qFromAngleAxis(0.0f, axis);
	qPrint("       q0", q0);

	Quaternion q1 = qFromAngleAxis(90.0f, axis);
	qPrint("       q1", q1);

	Quaternion qe = qFromAngleAxis(30.0f, axis);
	qPrint("       qe", qe);

	qPrint("  lerp(0)", qLerp(q0, q1, 0.0f));
	assert(qEqual(qLerp(q0, q1, 0.0f), q0));

	qPrint("  lerp(1)", qLerp(q0, q1, 1.0f));
	assert(qEqual(qLerp(q0, q1, 1.0f), q1));

	Quaternion qlerp = qLerp(q0, q1, 1/3.0f);
	qPrint("lerp(1/3)", qlerp);
	qPrintAngleAxis("lerp(1/3)", qlerp);

	assert(qEqual(qlerp, qe) == 0);
}

void qtest6()
{
	HEADER("TEST 6: SLERP")

	Vector axis = {0.0f, 1.0f, 0.0f, 1.0f};
	Quaternion q0 = qFromAngleAxis( 0.0f, axis);
	qPrint("        q0", q0);

	Quaternion q1 = qFromAngleAxis(90.0f, axis);
	qPrint("        q1", q1);

	Quaternion qe = qFromAngleAxis(30.0f, axis);
	qPrint("        qe", qe);

	qPrint("  slerp(0)", qSlerp(q0, q1, 0.0f));
	assert(qEqual(qSlerp(q0, q1, 0.0f), q0));

	qPrint("  slerp(1)", qSlerp(q0, q1, 1.0f));
	assert(qEqual(qSlerp(q0, q1, 1.0f), q1));

	Quaternion qslerp = qSlerp(q0, q1, 1/3.0f);
	qPrint("slerp(1/3)", qslerp);
	qPrintAngleAxis("slerp(1/3)", qslerp);

	assert(qEqual(qslerp, qe));
}

///////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
	qtest1();
	qtest2();
	qtest3();
	qtest4();
	qtest5();
	qtest6();

	exit(EXIT_SUCCESS);
}

///////////////////////////////////////////////////////////////////////