#include "mre.h"


void matrix44_identity(Matrix44* outm)
{
	outm->m[0][0] = outm->m[1][1] = outm->m[2][2] = outm->m[3][3] = 1.0f;
	outm->m[0][1] = outm->m[0][2] = outm->m[0][3] = 0.0f;
	outm->m[1][0] = outm->m[1][2] = outm->m[1][3] = 0.0f;
	outm->m[2][0] = outm->m[2][1] = outm->m[2][3] = 0.0f;
	outm->m[3][0] = outm->m[3][1] = outm->m[3][2] = 0.0f;
}

void matrix44_zero(Matrix44* outm)
{
	outm->m[0][0] = outm->m[0][1] = outm->m[0][2] = outm->m[0][3] = 0.0f;
	outm->m[1][0] = outm->m[1][1] = outm->m[1][2] = outm->m[1][3] = 0.0f;
	outm->m[2][0] = outm->m[2][1] = outm->m[2][2] = outm->m[2][3] = 0.0f;
	outm->m[3][0] = outm->m[3][1] = outm->m[3][2] = outm->m[3][3] = 0.0f;
}

void matrix44_mul_matrix44(Matrix44* outm, const Matrix44* m1, const Matrix44* m2)
{
	Matrix44 temp;
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			temp.m[j][i] = (m1->m[j][0] * m2->m[0][i]) +
				(m1->m[j][1] * m2->m[1][i]) +
				(m1->m[j][2] * m2->m[2][i]) +
				(m1->m[j][3] * m2->m[3][i]);
		}
	}
	outm[0] = temp;
}

/*
cot fovy的半角余切
aspect 屏幕宽高比
f,n   远近裁面距离
| cot/aspect  0      0        0 |
| 0			  cot	 0        0 |
| 0           0      f/(f-n)  1 |
| 0           0      fn/(n-f) 0 |
*/
void matrix44_perspective(Matrix44 *outm, float fovy, float aspect, float zn, float zf)
{
	float cot = 1.0f / (float)tan(fovy * 0.5f);

	matrix44_zero(outm);
	outm->m[0][0] = cot / aspect;
	outm->m[1][1] = cot;
	outm->m[2][2] = zf / (zf - zn);
	outm->m[2][3] = 1.0f;
	outm->m[3][2] = (zn * zf) / (zn - zf);
}

/*
r 对应向右方向基向量 相当于x轴
u 对应向上方向基向量 相当于y轴
d 对应向前方向基向量 相当于z轴
p 对应Eye位置
| r.x	u.x		d.x       0 |
| r.y	u.y		d.y       0 |
| r.z	u.z		d.z		 0 |
| -P*R	-P*U	-P*D     1 |
*/
void matrix44_view(Matrix44* outm, const Vector3* eye, const Vector3* lookat, const Vector3* up)
{
	Vector3 r, u, d;

	//计算向前向量
	vector3_sub(&d, lookat, eye);
	vector3_normalize(&d);
	//计算向右向量
	vector3_cross(&r, up, &d);
	vector3_normalize(&r);
	//计算向上向量
	vector3_cross(&u, &d, &r);

	outm->m[0][0] = r.x;
	outm->m[1][0] = r.y;
	outm->m[2][0] = r.z;
	outm->m[3][0] = -vector3_dot(&r, eye);

	outm->m[0][1] = u.x;
	outm->m[1][1] = u.y;
	outm->m[2][1] = u.z;
	outm->m[3][1] = -vector3_dot(&u, eye);

	outm->m[0][2] = d.x;
	outm->m[1][2] = d.y;
	outm->m[2][2] = d.z;
	outm->m[3][2] = -vector3_dot(&d, eye);

	outm->m[0][3] = outm->m[1][3] = outm->m[2][3] = 0.0f;
	outm->m[3][3] = 1.0f;
}

/*
u  旋转轴x分量
v  旋转轴y分量
w  旋转轴z分量
| uu+(1-uu)cos		uv(1-cos)+wsin		uw(1-cos)-vsin       0 |
| uv(1-cos)-wsin	vv+(1-vv)cos		vw(1-cos)+usin       0 |
| uw(1-cos)+vsin	vw(1-cos)-usin		ww+(1-ww)cos		 0 |
| 0					0					0				     1 |
*/
void matrix44_rotate_axis(Matrix44* outm, Vector3 axis, float angle)
{
	vector3_normalize(&axis);
	float u = axis.x;
	float v = axis.y;
	float w = axis.z;

	outm->m[0][0] = cosf(angle) + (u * u) * (1 - cosf(angle));
	outm->m[0][1] = u * v * (1 - cosf(angle)) + w * sinf(angle);
	outm->m[0][2] = u * w * (1 - cosf(angle)) - v * sinf(angle);
	outm->m[0][3] = 0;

	outm->m[1][0] = u * v * (1 - cosf(angle)) - w * sinf(angle);
	outm->m[1][1] = cosf(angle) + v * v * (1 - cosf(angle));
	outm->m[1][2] = w * v * (1 - cosf(angle)) + u * sinf(angle);
	outm->m[1][3] = 0;

	outm->m[2][0] = u * w * (1 - cosf(angle)) + v * sinf(angle);
	outm->m[2][1] = v * w * (1 - cosf(angle)) - u * sinf(angle);
	outm->m[2][2] = cosf(angle) + w * w * (1 - cosf(angle));
	outm->m[2][3] = 0;

	outm->m[3][0] = 0;
	outm->m[3][1] = 0;
	outm->m[3][2] = 0;
	outm->m[3][3] = 1;
}

/*
{ 1,	0,				0,				0 },
{ 0,	cos(angle), 	sin(angle),		0 },
{ 0,	-sin(angle),	cos(angle),		0 },
{ 0,	0,				0,				1 }
*/
void matrix44_rotation_x(Matrix44* outm, float angle)
{

	matrix44_zero(outm);

	outm->m[0][0] = outm->m[3][3] = 1;
	outm->m[1][1] = outm->m[2][2] = cosf(angle);
	outm->m[1][2] = sinf(angle);
	outm->m[2][1] = -sinf(angle);
}

/*
 { cos(angle),		0,			-sin(angle),			0 });
 { 0,				1,			0,						0 });
 { sin(angle),		0,			cos(angle),				0 });
 { 0,				0,			0,						1 });
*/
void matrix44_rotation_y(Matrix44* outm, float angle)
{
	matrix44_zero(outm);
	outm->m[1][1] = outm->m[3][3] = 1;
	outm->m[0][0] = outm->m[2][2] = cosf(angle);
	outm->m[0][2] = -sinf(angle);
	outm->m[2][0] = sinf(angle);
}

/*
 { cos(angle),	sin(angle),				0,		0 });
 { -sin(angle),	cos(angle),				0,		0 });
 { 0,					0,				1,		0 });
 { 0,					0,				0,		1 });
*/
void matrix44_rotation_z(Matrix44* outm, float angle)
{
	matrix44_zero(outm);

	outm->m[2][2] = outm->m[3][3] = 1;
	outm->m[0][0] = outm->m[1][1] = cosf(angle);
	outm->m[0][1] = sinf(angle);
	outm->m[1][0] = -sinf(angle);
}


void matrix44_rotation(Matrix44* outm, float pitch, float yaw,  float roll)
{
	Matrix44 mx;
	Matrix44 my;
	Matrix44 mz;

	matrix44_rotation_x(&mx, pitch);
	matrix44_rotation_y(&my, yaw);
	matrix44_rotation_z(&mz, roll);

	//outMatrix = [M_RY] x [M_RX] x [M_RZ]  
	matrix44_mul_matrix44(outm, &mx, &mz);
	matrix44_mul_matrix44(outm, outm, &my);
}