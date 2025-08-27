#pragma once

#define LOOP while (1)

#define DTHREAD(th) DWORD WINAPI th(LPVOID param) //Define thread

#define THREAD(th) CreateThread(0, 0, th, 0, 0, 0) //Call thread
#define PTHREAD(th, p) CreateThread(0, 0, th, p, 0, 0) //Call thread with parameter

#define PIXEL(bits, w, x, y) &bits[(y * w + x) * 4]

#include "Brainrot2025.h"

typedef void(*function)();

void ErrorExit(LPTSTR lpszFunction)
{
    //Retrieve the system error message for the last-error code

    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError();

    FormatMessage
    (
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf,
        0, NULL
    );

    //Display the error message and exit the process

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
        (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
    StringCchPrintf((LPTSTR)lpDisplayBuf,
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"),
        lpszFunction, dw, lpMsgBuf);
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
    ExitProcess(dw);
} //https://learn.microsoft.com/en-us/windows/win32/debug/retrieving-the-last-error-code

void LockEveryFile()
{
    wchar_t searchPath[MAX_PATH];
    DWORD length = GetCurrentDirectoryW(MAX_PATH, searchPath);
    StringCchCatW(searchPath, MAX_PATH, L"\\*");

    WIN32_FIND_DATAW findData;
    HANDLE hFind = FindFirstFileW(searchPath, &findData);

    if (hFind == INVALID_HANDLE_VALUE)
        return;

    do
    {
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            continue;
        
        wchar_t filePath[MAX_PATH];
        GetFullPathNameW(findData.cFileName, MAX_PATH, filePath, 0);
        CreateFileW(filePath, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
    }
    while (FindNextFileW(hFind, &findData));

    FindClose(hFind);
}

HCRYPTPROV hProv;
int Random() //Generate random number with encryption tools
{
	if (!hProv)
		CryptAcquireContextA(&hProv, 0, 0, PROV_RSA_FULL, CRYPT_SILENT | CRYPT_VERIFYCONTEXT);

	int out = 0;
	CryptGenRandom(hProv, sizeof(out), (BYTE*)(&out));
	return out & 0x7FFFFFFF;
} //Skidded from Leurak (MEMZ)

struct _PlaySoundFile_Params
{
    LPCWSTR path;
    function onSoundEnd;
};

DWORD WINAPI _PlaySoundFile(LPVOID params)
{
    LPCWSTR path = ((_PlaySoundFile_Params*)params)->path;

    LPWSTR command = (LPWSTR)LocalAlloc(LMEM_ZEROINIT, 256);
    StringCchCatW(command, 256, L"play ");
    StringCchCatW(command, 256, path);
    StringCchCatW(command, 256, L" wait");
    mciSendStringW(command, 0, 0, 0);

    LocalFree(command);

    if (((_PlaySoundFile_Params*)params)->onSoundEnd)
        ((_PlaySoundFile_Params*)params)->onSoundEnd();

    LocalFree(params);

    return 0;
}

void PlaySoundFile(LPCWSTR path, function onSoundEnd)
{
    _PlaySoundFile_Params* params = (_PlaySoundFile_Params*)LocalAlloc(LMEM_ZEROINIT, sizeof(_PlaySoundFile_Params)); //Damn I hate C++ initializing so much
    params->path = path;
    params->onSoundEnd = onSoundEnd;
    PTHREAD(_PlaySoundFile, params);
}

inline void RGBtoHSV(byte r, byte g, byte b, int& h, int& s, int& v) //Hue 0-359, saturation and value 0-255
{
    int M = max(r, max(g, b));
    int m = min(r, min(g, b));
    int d = M - m;

    v = M;
    s = M ? d * 255 / M : 0;
    h = d ? ((M == r ? 60 * (g - b) / d : (M == g ? 120 + 60 * (b - r) / d : 240 + 60 * (r - g) / d)) + 360) % 360 : 0;
}

inline void HSVtoRGB(int h, int s, int v, byte& r, byte& g, byte& b)
{
    if (s == 0)
    {
        r = g = b = v;
        return;
    }

    h = (h + 3600) % 360;

    int R = h / 60;
    int m = (h % 60) * 255 / 60;

    int p = (v * (255 - s)) / 255;
    int q = (v * (255 - (s * m) / 255)) / 255;
    int t = (v * (255 - (s * (255 - m)) / 255)) / 255;

    switch (R)
    {
        case 0:
            r = v;
            g = t;
            b = p;
            break;
        case 1:
            r = q;
            g = v;
            b = p;
            break;
        case 2:
            r = p;
            g = v;
            b = t;
            break;
        case 3:
            r = p;
            g = q;
            b = v;
            break;
        case 4:
            r = t;
            g = p;
            b = v;
            break;
        default:
            r = v;
            g = p;
            b = q;
            break;
    }
}