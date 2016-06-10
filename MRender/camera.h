#pragma once

Camera* camera_create_perspective(float fovy, float aspect_ratio, float clip_near, float clip_far);
void camera_destroy(Camera* camera);
void camera_set_position(Camera* camera, Vector3 pos);
void camera_lookat(Camera* camera, Vector3 eye, Vector3 lookat, Vector3 up);
