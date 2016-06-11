#pragma once

Light* light_create_point(Color color, Vector3 position);
void light_destory(Light* light);