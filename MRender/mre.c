#include "mre.h"

MREngine mre;

int engine_init(int width, int height, const TCHAR* title, HINSTANCE hinstance)
{
	memset(&mre, 0, sizeof(MREngine));

	mre.fps = 0;
	mre.frame_time_last = 0;

	if (window_init(&mre.window, width, height, title, hinstance))
	{
		printf("window init failed");
		return -1;
	}

	renderdev_init(&mre.renderdev, width, height, mre.window.screen_framebuf);
	mre.render_tick = NULL;

	return 0;
}

void engine_start(AppTick tick)
{
	mre.render_tick = tick;

	while (mre.window.exit == MRE_FALSE)
	{
		float now = (float)GetTickCount() * 0.001f;
		float time_delta = now - mre.frame_time_last;
		engine_tick(time_delta);
	}
}

void engine_tick(float time_delta)
{
	//处理Windows消息
	window_dispatch();


	//清理缓冲区
	renderdev_clear(&mre.renderdev);

	//提交渲染数据
	if (mre.render_tick != NULL)
	{
		mre.render_tick(time_delta);
	}

	//present
	window_present(&mre.window);

	//更新FPS
	engine_fps();
}

void engine_fps()
{
	float now = (float)GetTickCount() * 0.001f;

	if (now - mre.frame_time_last > 1.0f)
	{
		printf("FPS: %f\n", mre.fps);
		mre.frame_time_last = now;
		mre.fps = 0;
	}
	else
	{
		mre.fps++;
	}
}