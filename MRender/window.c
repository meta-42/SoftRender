#include "mre.h"

int window_init(Window* window, int w, int h, const TCHAR* title, HINSTANCE hinstance)
{
	window_close(window);

	WNDCLASSEX  winclass;
	winclass.cbSize = sizeof(WNDCLASSEX);
	//双击消息|DeviceContext|重绘宽|重绘高
	winclass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = (WNDPROC)window_events;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = hinstance;
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	winclass.lpszClassName = "winclass";
	winclass.lpszMenuName = NULL;

	RegisterClassEx(&winclass);

	window->handle = CreateWindowEx(
		NULL,								//窗口扩展样式
		"winclass",							//类名
		title,								//窗口标题
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,	//窗口样式
		0, 0,								//位置
		w, h,								//宽高
		NULL,								//父窗口
		NULL,								//菜单
		hinstance,							//程序实例句柄
		NULL								//其他参数
		);

	if (window->handle == NULL)
	{
		-1;
	}

	HDC hDC;
	window->exit = 0;
	hDC = GetDC(window->handle);
	window->context = CreateCompatibleDC(hDC);
	ReleaseDC(window->handle, hDC);

	LPVOID ptr;
	BITMAPINFO bi = { { sizeof(BITMAPINFOHEADER), w, -h, 1, 32, BI_RGB,
		w * h * 4, 0, 0, 0, 0 } };
	window->dib_cur = CreateDIBSection(window->context, &bi, DIB_RGB_COLORS, &ptr, 0, 0);
	if (window->dib_cur == NULL)
	{
		return -2;
	}

	window->dib_old = (HBITMAP)SelectObject(window->context, window->dib_cur);
	window->screen_framebuf = (unsigned char*)ptr;
	window->width = w;
	window->height = h;

	RECT rect = { 0, 0, w, h };
	int wx, wy, sx, sy;
	AdjustWindowRect(&rect, GetWindowLong(window->handle, GWL_STYLE), 0);
	wx = rect.right - rect.left;
	wy = rect.bottom - rect.top;
	sx = (GetSystemMetrics(SM_CXSCREEN) - wx) / 2;
	sy = (GetSystemMetrics(SM_CYSCREEN) - wy) / 2;
	if (sy < 0) sy = 0;

	SetWindowPos(window->handle, NULL, sx, sy, wx, wy, (SWP_NOCOPYBITS | SWP_NOZORDER | SWP_SHOWWINDOW));
	SetForegroundWindow(window->handle);
	ShowWindow(window->handle, SW_NORMAL);
	window_dispatch();

	memset(window->keys, 0, sizeof(int) * 512);
	memset(window->screen_framebuf, 0, w * h * 4);
	return 0;
}

int window_close(Window* window)
{
	if (window->context)
	{
		if (window->dib_old)
		{
			SelectObject(window->context, window->dib_old);
			window->dib_old = NULL;
		}
		DeleteDC(window->context);
		window->context = NULL;
	}

	if (window->dib_cur)
	{
		DeleteObject(window->dib_cur);
		window->dib_cur = NULL;
	}

	if (window->handle)
	{
		CloseWindow(window->handle);
		window->handle = NULL;
	}
	return 0;
}

void window_present(Window* window)
{
	HDC hDC = GetDC(window->handle);
	BitBlt(hDC, 0, 0, window->width, window->height, window->context, 0, 0, SRCCOPY);
	ReleaseDC(window->handle, hDC);
	window_dispatch();
}

void window_dispatch(void) 
{
	MSG msg;
	while (1)
	{
		if (!PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) break;
		if (!GetMessage(&msg, NULL, 0, 0)) break;
		DispatchMessage(&msg);
	}
}

static LRESULT window_events(HWND hWnd, UINT msg, WPARAM wParam, LRESULT lParam)
{
	switch (msg)
	{
		case WM_CLOSE: mre.window.exit = 1; break;
		case WM_KEYDOWN: mre.window.keys[wParam & 511] = 1; break;
		case WM_KEYUP: mre.window.keys[wParam & 511] = 0; break;
		default: return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}
