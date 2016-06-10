#pragma once

Mesh* mesh_create(char* meshname, char* texname);
void mesh_destroy(Mesh* mesh);
void mesh_load(Mesh* mesh, char* fillename);

void mesh_set_position(Mesh* mesh, Vector3 pos);
void mesh_set_scale(Mesh* mesh, Vector3 scl);
void mesh_set_rotation(Mesh* mesh, Vector3 rot);
void mesh_set_visible(Mesh* mesh, unsigned char visible);
void mesh_update_transform(Mesh* mesh);