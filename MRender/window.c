#include "mre.h"

int window_init(Window* window, int w, int h, const TCHAR* title)
{
	window_close(window);

	WNDCLASS wc =
	{
		CS_BYTEALIGNCLIENT,
		(WNDPROC)window_events,
		0,
		0,
		0,
		NULL,
		NULL,
		NULL,
		NULL,
		_T("SCREEN3.1415926")
	};

	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hInstance = GetModuleHandle(NULL);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	if (!RegisterClass(&wc))
	{
		return -1;
	}

	window->handle = CreateWindow
		(
			_T("SCREEN3.1415926"),
			title,
			WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
			0,
			0,
			0,
			0,
			NULL,
			NULL,
			wc.hInstance,
			NULL
			);

	if (window->handle == NULL)
	{
		-2;
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
		return -3;
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
