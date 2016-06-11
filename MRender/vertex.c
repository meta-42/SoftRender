#include "mre.h"


void vertex_rhw(Vertex* outvx)
{
	float rhw = 1.0f / outvx->pos.w;
	outvx->rhw = rhw;
	outvx->texcoord.u *= rhw;
	outvx->texcoord.v *= rhw;
	outvx->col.r *= rhw;
	outvx->col.g *= rhw;
	outvx->col.b *= rhw;
}

void vertex_interp(Vertex* outvx, const Vertex* vx1, const Vertex* vx2, float t)
{
	vector4_interp(&outvx->pos, &vx1->pos, &vx2->pos, t);
	outvx->texcoord.u = interp(vx1->texcoord.u, vx2->texcoord.u, t);
	outvx->texcoord.v = interp(vx1->texcoord.v, vx2->texcoord.v, t);
	outvx->col.r = interp(vx1->col.r, vx2->col.r, t);
	outvx->col.g = interp(vx1->col.g, vx2->col.g, t);
	outvx->col.b = interp(vx1->col.b, vx2->col.b, t);
	outvx->rhw = interp(vx1->rhw, vx2->rhw, t);
	outvx->rhw = interp(vx1->rhw, vx2->rhw, t);
}

void vertex_get_setp(Vertex* outvx, const Vertex* x1, const Vertex* x2, float width)
{
	float inv = 1.0f / width;
	outvx->pos.x = (x2->pos.x - x1->pos.x) * inv;
	outvx->pos.y = (x2->pos.y - x1->pos.y) * inv;
	outvx->pos.z = (x2->pos.z - x1->pos.z) * inv;
	outvx->pos.w = (x2->pos.w - x1->pos.w) * inv;
	outvx->texcoord.u = (x2->texcoord.u - x1->texcoord.u) * inv;
	outvx->texcoord.v = (x2->texcoord.v - x1->texcoord.v) * inv;
	outvx->col.r = (x2->col.r - x1->col.r) * inv;
	outvx->col.g = (x2->col.g - x1->col.g) * inv;
	outvx->col.b = (x2->col.b - x1->col.b) * inv;
	outvx->rhw = (x2->rhw - x1->rhw) * inv;
}

void vertex_roll(Vertex* outvx, const Vertex* step)
{
	outvx->pos.x += step->pos.x;
	outvx->pos.y += step->pos.y;
	outvx->pos.z += step->pos.z;
	outvx->pos.w += step->pos.w;
	outvx->rhw += step->rhw;
	outvx->texcoord.u += step->texcoord.u;
	outvx->texcoord.v += step->texcoord.v;
	outvx->col.r += step->col.r;
	outvx->col.g += step->col.g;
	outvx->col.b += step->col.b;
}
