#pragma once

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <string.h>
#include <windows.h>
#include <basetsd.h>
#include <assert.h>

#include "types.h"
#include "utile.h"
#include "renderdev.h"
#include "window.h"
#include "camera.h"
#include "vector.h"
#include "vertex.h"
#include "memory.h"
#include "texture.h"
#include "matrix.h"
#include "mesh.h"

#define MRE_INDEX_NONE				-1
#define MRE_INIT_SUCCEED			0
#define MRE_TRUE					1
#define MRE_FALSE					0

#define RESOURCES_PATH				"..\\Resources\\"

#define RENDER_STATE_WIREFRAME      1		// ��Ⱦ�߿�
#define RENDER_STATE_TEXTURE        2		// ��Ⱦ����
#define RENDER_STATE_COLOR          4		// ��Ⱦ��ɫ
#define RENDER_STATE_VERTEX         8		// ��Ⱦ��c

#define TEXTURE_SIZE_MAX	        256		// �����������

typedef void(*AppTick)(float);

typedef struct
{

	Window window;
	Renderdev renderdev;
	float fps;
	float frame_time_last;

	AppTick logic_tick;
	AppTick physics_tick;
	AppTick render_tick;

} MREngine;

extern MREngine mre;

int engine_init(int width, int height, const TCHAR* title);
void engine_start(AppTick tick);
void engine_tick(float time_delta);
void engine_fps();

