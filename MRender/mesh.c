#include "mre.h"

Mesh* mesh_create(char* meshname, char* texname)
{
	Mesh* mesh = (Mesh*)malloc(sizeof(Mesh));
	memset(mesh, 0, sizeof(Mesh));

	mesh->position = vector3_zero();
	mesh->rotation = vector3_zero();
	mesh->scale = vector3_one();
	mesh->visible = MRE_TRUE;
	strcpy(mesh->name, meshname);

	matrix44_identity(&mesh->matrix_world);

	char *result = malloc(strlen(RESOURCES_PATH) + strlen(meshname) + 1);
	strcpy(result, RESOURCES_PATH);
	strcat(result, meshname);
	char* path = result;
	mesh_load(mesh, path);

	Texture* tmpTex = texture_create(texname);
	mesh->texture = *tmpTex;
	return mesh;
}

void mesh_destroy(Mesh* mesh)
{
	if (mesh)
	{
		free(mesh);
		mesh = NULL;
	}
}

void mesh_load(Mesh* mesh, char* fillename)
{
	Memory *memory = mopen(fillename);

	if (!memory)
	{
		return mesh;
	}
	else
	{
		char* line = strtok((char*)memory->buffer, "\n");

		Vector3 vec3;
		Vector3 normal;
		Texcoord texcoord;
		Face face;

		face.vertex_index[0] =
		face.vertex_index[1] =
		face.vertex_index[2] =
		face.texcoord_index[0] =
		face.texcoord_index[1] =
		face.texcoord_index[2] = MRE_INDEX_NONE;

		while (line)
		{
			if (!line[0] || line[0] == '#')
			{
				line = strtok(NULL, "\n");
				continue;
			}
			else if (line[0] == 'f' && line[1] == ' ')
			{
				int vertex_index[3] = { 0,0,0 };


				if (sscanf(line, "f %d %d %d", 
					&face.vertex_index[0],
					&face.vertex_index[1],
					&face.vertex_index[2]) == 3)
				{
					mesh->useuv = 0;
				}

				if (sscanf(line, "f %d/%d %d/%d %d/%d",
					&face.vertex_index[0],
					&face.texcoord_index[0],
					&face.vertex_index[1],
					&face.texcoord_index[1],
					&face.vertex_index[2],
					&face.texcoord_index[2]) == 6)
				{
					mesh->useuv = 1;
				}

				if (sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
					&face.vertex_index[0],
					&face.texcoord_index[0],
					&face.normal_index[0],
					&face.vertex_index[1],
					&face.texcoord_index[1],
					&face.normal_index[1],
					&face.vertex_index[2],
					&face.texcoord_index[2],
					&face.normal_index[2]) == 9)
				{
					mesh->useuv = 1;
				}

				mesh->n_face++;
				mesh->faces = (Face*)realloc(mesh->faces, mesh->n_face * sizeof(Face));
				memcpy(&mesh->faces[mesh->n_face - 1], &face, sizeof(Face));
				printf("f %d/%d/%d %d/%d/%d %d/%d/%d\n",
					mesh->faces[mesh->n_face - 1].vertex_index[0],
					mesh->faces[mesh->n_face - 1].texcoord_index[0],
					mesh->faces[mesh->n_face - 1].normal_index[0],
					mesh->faces[mesh->n_face - 1].vertex_index[1],
					mesh->faces[mesh->n_face - 1].texcoord_index[1],
					mesh->faces[mesh->n_face - 1].normal_index[1],
					mesh->faces[mesh->n_face - 1].vertex_index[2],
					mesh->faces[mesh->n_face - 1].texcoord_index[2],
					mesh->faces[mesh->n_face - 1].normal_index[2]);

			}
			else if (sscanf(line, "v %f %f %f", &vec3.x, &vec3.y, &vec3.z) == 3)
			{
				mesh->n_vertex++;

				mesh->vertices = (Vector3*)realloc(mesh->vertices, mesh->n_vertex * sizeof(Vector3));

				vec3.x += 0.001f;
				vec3.y += 0.001f;
				vec3.z += 0.001f;
				memcpy(&mesh->vertices[mesh->n_vertex - 1], &vec3, sizeof(Vector3));
				printf("v %f %f %f\n", mesh->vertices[mesh->n_vertex - 1].x, mesh->vertices[mesh->n_vertex - 1].y, mesh->vertices[mesh->n_vertex - 1].z);
			}
			else if (sscanf(line, "vt %f %f", &texcoord.u, &texcoord.v) == 2)
			{
				mesh->n_texcord++;
				
				mesh->texcoords = (Texcoord*)realloc(mesh->texcoords, mesh->n_texcord * sizeof(Texcoord));
				memcpy(&mesh->texcoords[mesh->n_texcord - 1], &texcoord, sizeof(Texcoord));
				printf("vt %f %f\n", mesh->texcoords[mesh->n_texcord - 1].u, mesh->texcoords[mesh->n_texcord - 1].v);
			}
			else if (sscanf(line, "vn %f %f %f", &normal.x, &normal.y, &normal.z) == 3)
			{
				mesh->n_normal++;

				mesh->normals = (Vector3*)realloc(mesh->normals, mesh->n_normal * sizeof(Vector3));
				memcpy(&mesh->normals[mesh->n_normal - 1], &normal, sizeof(Vector3));
				printf("vn %f %f %f\n", mesh->normals[mesh->n_normal - 1].x, mesh->normals[mesh->n_normal - 1].y, mesh->normals[mesh->n_normal - 1].z);
			}

			line = strtok(NULL, "\n");
		}
		mclose(memory);
	}
	
	mesh_gen_face_normals(mesh);
	printf("Vertices num = %d\n", mesh->n_vertex);
	printf("Face num = %d\n", mesh->n_face);
}

void mesh_gen_face_normals(Mesh* mesh)
{
	for (int i = 0; i < mesh->n_face; i++)
	{
		Face face = mesh->faces[i];
		Vector3 veca = mesh->normals[face.normal_index[0]-1];
		Vector3 vecb = mesh->normals[face.normal_index[1]-1];
		Vector3 vecc = mesh->normals[face.normal_index[2]-1];

		Vector3 nor;
		vector3_add(&nor, &veca, &vecb);
		vector3_add(&nor, &nor, &vecc);
		vector3_div(&nor, 3);
		vector3_normalize(&nor);
		mesh->faces[i].normal = nor;
	}
}

void mesh_set_position(Mesh* mesh, Vector3 pos)
{
	mesh->position = pos;
	mesh_update_transform(mesh);
}

void mesh_set_scale(Mesh* mesh, Vector3 scl)
{
	mesh->scale = scl;
}

void mesh_set_rotation(Mesh* mesh, Vector3 rot)
{
	mesh->rotation = rot;
	mesh_update_transform(mesh);
}

void mesh_set_visible(Mesh* mesh, unsigned char visible)
{
	mesh->visible = visible;
}

void mesh_update_transform(Mesh* mesh)
{
	matrix44_identity(&mesh->matrix_world);
	matrix44_rotation(&mesh->matrix_world, mesh->rotation.x, mesh->rotation.y, mesh->rotation.z);
	mesh->matrix_world.m[3][0] = mesh->position.x;
	mesh->matrix_world.m[3][1] = mesh->position.y;
	mesh->matrix_world.m[3][2] = mesh->position.z;
}
