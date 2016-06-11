#pragma once

float vector4_length(const Vector4* v);
void vector4_normalize(Vector4* outv);
void vector4_add(Vector4* outv, const Vector4* v1, const Vector4* v2);
void vector4_sub(Vector4* outv, const Vector4* v1, const Vector4* v2);
float vector4_dot(const Vector4* v1, const Vector4* v2);
void vector4_cross(Vector4* outv, const Vector4* v1, const Vector4* v2);
Vector4 vector4_one();

void vector4_div(Vector4* outv, float x);
void vector4_mul(Vector4* outv, const Vector4* v, const Matrix44* m);
void vector4_interp(Vector4* outv, const Vector4 *v1, const Vector4 *v2, float t);
void vector4_rhw(Vector4* outv, const Vector4* v);

void vector3_mul(Vector3* outv, const Vector3* v, const Matrix44* m);
float vector3_length(const Vector3* v);
void vector3_normalize(Vector3* outv);
void vector3_add(Vector3* outv, const Vector3* v1, const Vector3* v2);
void vector3_sub(Vector3* outv, const Vector3* v1, const Vector3* v2);
float vector3_dot(const Vector3* v1, const Vector3* v2);
void vector3_cross(Vector3* outv, const Vector3* v1, const Vector3* v2);
void vector3_div(Vector4* outv, float x);

Vector3 vector3_zero();
Vector3 vector3_one();