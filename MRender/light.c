#include "mre.h"

Light* light_create_point(Color color, Vector3 position)
{
	Light *light = (Light *)malloc(sizeof(Light));

	light->light_type = 1;

	memcpy(&light->color, &color, sizeof(Color));

	memcpy(&light->position, &position, sizeof(Vector3));

	return light;
}

void light_destory(Light* light)
{
	if (light)
	{
		free(light);
		light = NULL;
	}
}

