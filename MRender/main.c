#pragma once
#include "mre.h"

Mesh mesh;
Camera camera;
int screen_width = 800, screen_height = 600;

void tick(float time_delta);
void start();

int main(void)
{
	TCHAR* title = _T("MRenderEngine");

	if (engine_init(screen_width, screen_height, title) == MRE_INIT_SUCCEED)
	{
		start();
		engine_start(&tick);
	}
	return 0;
}

void start()
{
	//创建相机
	float aspect = (float)screen_width / (float)screen_height;
	float fovy = 3.14 / 2.f;
	float clip_near = 1.f;
	float clip_far = 500.f;
	camera = *camera_create_perspective(fovy, aspect, clip_near, clip_far);
	Vector3 eye = { 0.f,0.f,-1.f }, lookat = { 0.f, 0.f, 0.f }, up = { 0.f, 1.f,0.f };
	camera_lookat(&camera, eye, lookat, up);
	renderdev_set_camera(&mre.renderdev, camera);

	//创建mesh
	mesh = *mesh_create("mono.obj", "mono.bmp");
	Vector3 position = vector3_zero();
	mesh_set_position(&mesh, position);
	Vector3 rotation = vector3_zero();
	mesh_set_rotation(&mesh, rotation);

	//控制相机
	Vector3 camera_pos = vector3_zero();
	camera_pos.z = -2;
	camera_set_position(&camera, camera_pos);

	mre.renderdev.render_state = RENDER_STATE_TEXTURE;
}

float x = 1;
float y = 1;
void tick(float time_delta)
{
	//printf("%f", time_delta);
	if (mre.window.keys[VK_LEFT])	x += time_delta * 0.1f;
	if (mre.window.keys[VK_RIGHT])	x -= time_delta * 0.1f;
	if (mre.window.keys[VK_UP])		y -= time_delta * 0.1f;
	if (mre.window.keys[VK_DOWN])	y += time_delta * 0.1f;

	Vector3 rotation = { 0, x, 0 };
	mesh_set_rotation(&mesh, rotation);

	Vector3 position = vector3_zero();
	position.z = y;
	mesh_set_position(&mesh, position);

	renderdev_draw_mesh(&mre.renderdev, mesh);
}
