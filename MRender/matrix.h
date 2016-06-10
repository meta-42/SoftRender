#pragma once

void matrix44_identity(Matrix44* outm);
void matrix44_zero(Matrix44* outm);
void matrix44_mul_matrix44(Matrix44* outm, const Matrix44* m1, const Matrix44* m2);
void matrix44_perspective(Matrix44 *outm, float fovy, float aspect, float zn, float zf);
void matrix44_view(Matrix44* outm, const Vector3* eye, const Vector3* lookat, const Vector3* up);
void matrix44_rotate_axis(Matrix44* outm, Vector3 axis, float angle);
void matrix44_rotation_x(Matrix44* outm, float angle);
void matrix44_rotation_y(Matrix44* outm, float angle);
void matrix44_rotation_z(Matrix44* outm, float angle);
void matrix44_rotation(Matrix44* outm, float pitch, float yaw, float roll);