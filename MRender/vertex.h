#pragma once

void vertex_rhw(Vertex* outvx);
void vertex_interp(Vertex* outvx, const Vertex* vx1, const Vertex* vx2, float t);
void vertex_get_setp(Vertex* outvx, const Vertex* x1, const Vertex* x2, float width);
void vertex_roll(Vertex* outvx, const Vertex* step);