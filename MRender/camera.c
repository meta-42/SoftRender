#include "mre.h"

Camera* camera_create_perspective(float fovy, float aspect_ratio, float clip_near, float clip_far)
{
	Camera* camera = malloc(sizeof(Camera));
	memset(camera, 0, sizeof(Camera));

	camera->fovy = fovy;
	camera->aspect_ratio = aspect_ratio;
	camera->clip_far = clip_far;
	camera->clip_near = clip_near;

	matrix44_identity(&camera->matrix_view);
	matrix44_perspective(&camera->matrix_projection, fovy, aspect_ratio, clip_near, clip_far);
	return camera;
}

void camera_destroy(Camera* camera)
{
	if (camera)
	{
		free(camera);
		camera = NULL;
	}
}

void camera_set_position(Camera* camera, Vector3 pos)
{
	camera_lookat(camera, pos, camera->lookat, camera->up_direction);
}

void camera_lookat(Camera* camera, Vector3 eye, Vector3 lookat, Vector3 up)
{
	camera->position = eye;
	camera->lookat = lookat;
	camera->up_direction = up;
	matrix44_view(&camera->matrix_view, &camera->position, &camera->lookat, &camera->up_direction);
	renderdev_set_camera(&mre.renderdev, *camera);
}
