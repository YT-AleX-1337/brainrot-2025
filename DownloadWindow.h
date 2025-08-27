#pragma once

DTHREAD(DownloadWindowProc);

DTHREAD(BIMessage)
{
	MessageBoxW(0, L"severe brainrot detected", L"uh oh...", MB_ICONERROR | MB_SYSTEMMODAL);

	return 0;
}

DTHREAD(BadIdea)
{
	for (int i = 0; i < 10; i++)
	{
		THREAD(BIMessage);
		Sleep(100);
	}

	return 0;
}

LRESULT WINAPI SquidchadWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
	case WM_LBUTTONDOWN:
		THREAD(BadIdea);
		break;
	case WM_PAINT:
		hbmp = (HBITMAP)LoadImageW(0, L"DOWNLOAD.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		dHdc = GetDC(hwnd);
		sHdc = CreateCompatibleDC(0);
		SelectObject(sHdc, hbmp);
		StretchBlt(dHdc, 0, 0, 400, 280, sHdc, 0, 0, 400, 300, SRCCOPY);
		DeleteDC(sHdc);
		DeleteObject(hbmp);
		break;
	}
	return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

LRESULT WINAPI XavierWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
	case WM_LBUTTONDOWN:
		THREAD(BadIdea);
		break;
	case WM_PAINT:
		hbmp = (HBITMAP)LoadImageW(0, L"XAVIER.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		dHdc = GetDC(hwnd);
		sHdc = CreateCompatibleDC(0);
		SelectObject(sHdc, hbmp);
		StretchBlt(dHdc, 0, 0, 400, 280, sHdc, 0, 0, 400, 300, SRCCOPY);
		DeleteDC(sHdc);
		DeleteObject(hbmp);
		break;
	}
	return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

LRESULT WINAPI MuscWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
	case WM_LBUTTONDOWN:
		THREAD(BadIdea);
		break;
	case WM_PAINT:
		hbmp = (HBITMAP)LoadImageW(0, L"MUSC.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		dHdc = GetDC(hwnd);
		sHdc = CreateCompatibleDC(0);
		SelectObject(sHdc, hbmp);
		StretchBlt(dHdc, 0, 0, 400, 280, sHdc, 0, 0, 400, 300, SRCCOPY);
		DeleteDC(sHdc);
		DeleteObject(hbmp);
		break;
	}
	return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

LRESULT WINAPI BobuxWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
	case WM_LBUTTONDOWN:
		THREAD(BadIdea);
		break;
	case WM_PAINT:
		hbmp = (HBITMAP)LoadImageW(0, L"BOBUX.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		dHdc = GetDC(hwnd);
		sHdc = CreateCompatibleDC(0);
		SelectObject(sHdc, hbmp);
		StretchBlt(dHdc, 0, 0, 400, 280, sHdc, 0, 0, 400, 300, SRCCOPY);
		DeleteDC(sHdc);
		DeleteObject(hbmp);
		break;
	}
	return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

LRESULT WINAPI TekWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
	case WM_LBUTTONDOWN:
		THREAD(BadIdea);
		break;
	case WM_PAINT:
		hbmp = (HBITMAP)LoadImageW(0, L"TEK.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		dHdc = GetDC(hwnd);
		sHdc = CreateCompatibleDC(0);
		SelectObject(sHdc, hbmp);
		StretchBlt(dHdc, 0, 0, 400, 280, sHdc, 0, 0, 400, 300, SRCCOPY);
		DeleteDC(sHdc);
		DeleteObject(hbmp);
		break;
	}
	return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

LRESULT WINAPI AreaWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
	case WM_LBUTTONDOWN:
		THREAD(BadIdea);
		break;
	case WM_PAINT:
		hbmp = (HBITMAP)LoadImageW(0, L"AREA.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		dHdc = GetDC(hwnd);
		sHdc = CreateCompatibleDC(0);
		SelectObject(sHdc, hbmp);
		StretchBlt(dHdc, 0, 0, 400, 280, sHdc, 0, 0, 400, 300, SRCCOPY);
		DeleteDC(sHdc);
		DeleteObject(hbmp);
		break;
	}
	return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

LRESULT WINAPI IponWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
	case WM_LBUTTONDOWN:
		THREAD(BadIdea);
		break;
	case WM_PAINT:
		hbmp = (HBITMAP)LoadImageW(0, L"IPON.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		dHdc = GetDC(hwnd);
		sHdc = CreateCompatibleDC(0);
		SelectObject(sHdc, hbmp);
		StretchBlt(dHdc, 0, 0, 400, 280, sHdc, 0, 0, 400, 300, SRCCOPY);
		DeleteDC(sHdc);
		DeleteObject(hbmp);
		break;
	}
	return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

LRESULT WINAPI PopWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
	case WM_LBUTTONDOWN:
		THREAD(BadIdea);
		break;
	case WM_PAINT:
		hbmp = (HBITMAP)LoadImageW(0, L"POP.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		dHdc = GetDC(hwnd);
		sHdc = CreateCompatibleDC(0);
		SelectObject(sHdc, hbmp);
		StretchBlt(dHdc, 0, 0, 400, 280, sHdc, 0, 0, 400, 300, SRCCOPY);
		DeleteDC(sHdc);
		DeleteObject(hbmp);
		break;
	}
	return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

LRESULT WINAPI RamWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
	case WM_LBUTTONDOWN:
		THREAD(BadIdea);
		break;
	case WM_PAINT:
		hbmp = (HBITMAP)LoadImageW(0, L"RAM.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		dHdc = GetDC(hwnd);
		sHdc = CreateCompatibleDC(0);
		SelectObject(sHdc, hbmp);
		StretchBlt(dHdc, 0, 0, 400, 280, sHdc, 0, 0, 400, 300, SRCCOPY);
		DeleteDC(sHdc);
		DeleteObject(hbmp);
		break;
	}
	return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

int previous = -1;
DTHREAD(DownloadWindow)
{
	WNDCLASS wc = { };

	LPCWSTR CLASS_NAME_1 = L"AX1337-SEVENCH-DOWNLOAD";
	wc.lpfnWndProc = SquidchadWindowProc;
	wc.lpszClassName = CLASS_NAME_1;
	RegisterClassW(&wc);

	LPCWSTR CLASS_NAME_2 = L"AX1337-SEVENCH-XAVIER";
	wc.lpfnWndProc = XavierWindowProc;
	wc.lpszClassName = CLASS_NAME_2;
	RegisterClassW(&wc);

	LPCWSTR CLASS_NAME_3 = L"AX1337-SEVENCH-MUSC";
	wc.lpfnWndProc = MuscWindowProc;
	wc.lpszClassName = CLASS_NAME_3;
	RegisterClassW(&wc);

	LPCWSTR CLASS_NAME_4 = L"AX1337-SEVENCH-BOBUX";
	wc.lpfnWndProc = BobuxWindowProc;
	wc.lpszClassName = CLASS_NAME_4;
	RegisterClassW(&wc);

	LPCWSTR CLASS_NAME_5 = L"AX1337-SEVENCH-TEK";
	wc.lpfnWndProc = TekWindowProc;
	wc.lpszClassName = CLASS_NAME_5;
	RegisterClassW(&wc);

	LPCWSTR CLASS_NAME_6 = L"AX1337-SEVENCH-AREA";
	wc.lpfnWndProc = AreaWindowProc;
	wc.lpszClassName = CLASS_NAME_6;
	RegisterClassW(&wc);

	LPCWSTR CLASS_NAME_7 = L"AX1337-SEVENCH-IPON";
	wc.lpfnWndProc = IponWindowProc;
	wc.lpszClassName = CLASS_NAME_7;
	RegisterClassW(&wc);

	LPCWSTR CLASS_NAME_8 = L"AX1337-SEVENCH-POP";
	wc.lpfnWndProc = PopWindowProc;
	wc.lpszClassName = CLASS_NAME_8;
	RegisterClassW(&wc);

	LPCWSTR CLASS_NAME_9 = L"AX1337-SEVENCH-RAM";
	wc.lpfnWndProc = RamWindowProc;
	wc.lpszClassName = CLASS_NAME_9;
	RegisterClassW(&wc);

	LPCWSTR classes[] = { CLASS_NAME_1, CLASS_NAME_2, CLASS_NAME_3, CLASS_NAME_4, CLASS_NAME_5, CLASS_NAME_6, CLASS_NAME_7, CLASS_NAME_8, CLASS_NAME_9 };

	int chosen;
	do
	{
		chosen = Random() % 9;
	}
	while (chosen == previous);
	previous = chosen;

	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	HWND hwnd = CreateWindowExW(WS_EX_TOPMOST, classes[chosen], L"advertoosement", WS_SYSMENU,
		Random() % (w / 2) + w / 4 - 200, Random() % (h / 2) + h / 4 - 150, 400, 300, 0, 0, 0, 0);

	if (!hwnd) return 0;
	ShowWindow(hwnd, SW_SHOW);

	MSG msg = { };
	while (GetMessageW(&msg, 0, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	return 0;
}