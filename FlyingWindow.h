//Scrapped idea

#pragma once

LRESULT WINAPI FlyingWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HBITMAP hbmp;
	HDC dHdc;
	HDC sHdc;

	switch (uMsg)
	{
	case WM_SYSCOMMAND:
		if (wParam == SC_MINIMIZE || wParam == SC_MAXIMIZE)
			return 0;
		break;
	case WM_PAINT:
		hbmp = (HBITMAP)LoadImageW(0, L"SPAM.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		dHdc = GetDC(hwnd);
		sHdc = CreateCompatibleDC(0);
		SelectObject(sHdc, hbmp);
		StretchBlt(dHdc, 0, 0, 600, 280, sHdc, 0, 0, 800, 400, SRCCOPY);
		DeleteDC(sHdc);
		DeleteObject(hbmp);
		break;
	case WM_CLOSE:
	case WM_DESTROY:
	case WM_QUIT:
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

DWORD WINAPI MakeItFly(LPVOID hwnd)
{
	HWND _hwnd = (HWND)hwnd;

	int x = 1;
	int y = 1;
	int speed = 50;

	LOOP
	{
		RECT rect; //Get rect
		GetWindowRect(_hwnd, &rect);
		SetWindowPos(_hwnd, HWND_TOPMOST, rect.left + x * speed, rect.top + y * speed, 0, 0, SWP_NOSIZE);
		ShowWindow(_hwnd, SW_NORMAL);

		int w = GetSystemMetrics(SM_CXSCREEN);
		int h = GetSystemMetrics(SM_CYSCREEN);
		if (x == 1 & w < rect.right)
			x = -1;
		else if (x == -1 && 0 > rect.left)
			x = 1;
		if (y == 1 & h < rect.bottom)
			y = -1;
		else if (y == -1 && 0 > rect.top)
			y = 1;

		Sleep(100);
	}
}

DWORD WINAPI FlyingWindow(LPVOID)
{
	const wchar_t CLASS_NAME[] = L"AX1337-SEVENCH-FLYING";

	WNDCLASS wc = { };
	wc.lpfnWndProc = FlyingWindowProc;
	wc.lpszClassName = CLASS_NAME;
	RegisterClassW(&wc);

	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	HWND hwnd = CreateWindowExW(WS_EX_TOPMOST, CLASS_NAME, L"hi ther", WS_SYSMENU,
		Random() % (w / 2) + w / 4 - 300, Random() % (h / 2) + h / 4 - 150, 600, 300, 0, 0, 0, 0);

	if (!hwnd) return 0;
	ShowWindow(hwnd, SW_SHOW);

	PTHREAD(MakeItFly, hwnd);

	MSG msg = { };
	while (GetMessageW(&msg, 0, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	return 0;
}