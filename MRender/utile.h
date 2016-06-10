#pragma once

#define MAX(a,b) ( ((a)>(b)) ? (a):(b) )
#define MIN(a,b) ( ((a)>(b)) ? (b):(a) )
#define DEG_TO_RAD	M_PI / 180.0f
#define RAD_TO_DEG	90.0f / M_PI

static inline float interp(float x1, float x2, float t)
{
	float temp = MAX(0, MIN(t, 1));
	return x1 + (x2 - x1) * temp;
}

static inline int clamp(int outi, int min, int max)
{
	return (outi < min) ? min : ((outi > max) ? max : outi);
}
