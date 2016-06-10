#pragma once

typedef struct
{
	float m[4][4];
} Matrix44;

typedef struct
{
	float x, y, z, w;
} Vector4;

typedef struct
{
	float x, y, z;
} Vector3;

typedef struct
{
	float x, y;
} Vector2;

typedef struct
{
	float r, g, b;
} Color;


typedef struct
{
	int vertex_index[3];
	int texcoord_index[3];
	int normal_index[3];
}Face;

typedef struct
{
	float u, v;
} Texcoord;

typedef struct
{
	float		fovy;
	float		aspect_ratio;
	float		clip_near;
	float		clip_far;

	Vector3		position;
	Vector3		lookat;
	Vector3		up_direction;

	Matrix44	matrix_projection;
	Matrix44	matrix_view;

} Camera;


typedef struct
{
	int width;
	int height;
	UINT32 texbuf[256][256];

}Texture;

typedef struct
{
	char name[64];

	unsigned char visible;
	unsigned char useuv;

	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

	unsigned int	n_vertex;
	unsigned int	n_face;
	unsigned int    n_texcord;
	unsigned int    n_normal;

	Texcoord* texcoords;	//[uv数组]
	Vector3* vertices;		//[顶点数组]
	Vector3* normals;		//[法线数组]
	Face*   faces;			//[面数组]

	Matrix44 matrix_world;

	Texture texture;

}Mesh;


typedef struct
{
	Vector4 pos;
	Texcoord texcoord;
	Color col;
	float rhw;					//Reciprocal of Homogeneous W
} Vertex;

