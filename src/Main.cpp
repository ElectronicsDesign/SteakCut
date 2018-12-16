#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include "DxLib.h"
#include "MenuArea.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	SetGraphMode(1280, 800, 32);
	SetWindowSize(1280, 800);
	SetMainWindowText("SteakCut - Ver 1.5");
	SetWindowIconID(101);

	if (ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK || DxLib_Init() == -1) return -1;
	LoadMem();

	return 0;
}