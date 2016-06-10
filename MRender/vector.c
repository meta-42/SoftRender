#include "mre.h"

float vector4_length(const Vector4* v)
{
	float squareLength = v->x * v->x + v->y * v->y + v->z * v->z;
	return (float)sqrt(squareLength);
}

void vector4_normalize(Vector4* outv)
{
	float length = vector4_length(outv);

	if (length != 0.0f)
	{
		float inv = 1 / length;
		outv->x *= inv;
		outv->y *= inv;
		outv->z *= inv;
	}
}

void vector4_add(Vector4* outv, const Vector4* v1, const Vector4* v2)
{
	outv->x = v1->x + v2->x;
	outv->y = v1->y + v2->y;
	outv->z = v1->z + v2->z;
	outv->w = 1.0;
}

void vector4_sub(Vector4* outv, const Vector4* v1, const Vector4* v2)
{
	outv->x = v1->x - v2->x;
	outv->y = v1->y - v2->y;
	outv->z = v1->z - v2->z;
	outv->w = 1.0;
}

float vector4_dot(const Vector4* v1, const Vector4* v2)
{
	return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

void vector4_cross(Vector4* outv, const Vector4* v1, const Vector4* v2)
{
	outv->x = v1->y * v2->z - v1->z * v2->y;
	outv->y = v1->z * v2->x - v1->x * v2->z;
	outv->z = v1->x * v2->y - v1->y * v2->x;
	outv->w = 1.0f;
}

void vector4_div(Vector4* outv, float x)
{
	float inv = 1.0f / x;
	outv->x *= inv;
	outv->y *= inv;
	outv->z *= inv;
	outv->w = 1.0f;
}

void vector4_mul(Vector4* outv, const Vector4* v, const Matrix44* m)
{
	float x = v->x * m->m[0][0] + v->y * m->m[1][0] + v->z * m->m[2][0] + v->w * m->m[3][0];
	float y = v->x * m->m[0][1] + v->y * m->m[1][1] + v->z * m->m[2][1] + v->w * m->m[3][1];
	float z = v->x * m->m[0][2] + v->y * m->m[1][2] + v->z * m->m[2][2] + v->w * m->m[3][2];
	float w = v->x * m->m[0][3] + v->y * m->m[1][3] + v->z * m->m[2][3] + v->w * m->m[3][3];

	outv->x = x;
	outv->y = y;
	outv->z = z;
	outv->w = w;
}

void vector4_interp(Vector4* outv, const Vector4 *v1, const Vector4 *v2, float t)
{
	outv->x = interp(v1->x, v2->x, t);
	outv->y = interp(v1->y, v2->y, t);
	outv->z = interp(v1->z, v2->z, t);
	outv->w = 1.0f;
}

void vector4_rhw(Vector4* outv, const Vector4* v)
{
	float rhw = 1 / v->w;
	outv->x = v->x * rhw;
	outv->y = v->y * rhw;
	outv->z = v->z * rhw;
	outv->w = 1.0f;
}

float vector3_length(const Vector3* v)
{
	float squareLength = v->x * v->x + v->y * v->y + v->z * v->z;
	return (float)sqrt(squareLength);
}

void vector3_normalize(Vector3* outv)
{
	float length = vector3_length(outv);

	if (length != 0.0f)
	{
		float inv = 1 / length;
		outv->x *= inv;
		outv->y *= inv;
		outv->z *= inv;
	}
}

void vector3_add(Vector3* outv, const Vector3* v1, const Vector3* v2)
{
	outv->x = v1->x + v2->x;
	outv->y = v1->y + v2->y;
	outv->z = v1->z + v2->z;
}

void vector3_sub(Vector3* outv, const Vector3* v1, const Vector3* v2)
{
	outv->x = v1->x - v2->x;
	outv->y = v1->y - v2->y;
	outv->z = v1->z - v2->z;
}

float vector3_dot(const Vector3* v1, const Vector3* v2)
{
	return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

void vector3_cross(Vector3* outv, const Vector3* v1, const Vector3* v2)
{
	outv->x = v1->y * v2->z - v1->z * v2->y;
	outv->y = v1->z * v2->x - v1->x * v2->z;
	outv->z = v1->x * v2->y - v1->y * v2->x;
}

Vector3 vector3_zero()
{
	Vector3 outv;
	outv.x = 0.f;
	outv.y = 0.f;
	outv.z = 0.f;
	return outv;
}

Vector3 vector3_one()
{
	Vector3 outv;
	outv.x = 1.f;
	outv.y = 1.f;
	outv.z = 1.f;
	return outv;
}
