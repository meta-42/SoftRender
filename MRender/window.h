#pragma once

typedef struct 
{
	int width;
	int height;
	int keys[512];
	int exit;
	HWND handle;
	HDC context;
	unsigned char* screen_framebuf;

	HBITMAP dib_cur;				//当前位图
	HBITMAP dib_old;				//被替换下来的位图，程序关闭时替换回去

}Window;

int window_init(Window* window, int w, int h, const TCHAR* title, HINSTANCE hinstance);
int window_close(Window* window);
void window_present(Window* window);
void window_dispatch();
LRESULT CALLBACK window_proc(HWND hWnd, UINT msg, WPARAM wParam, LRESULT lParam);

