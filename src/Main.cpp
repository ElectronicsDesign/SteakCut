#define _CRT_SECURE_NO_WARNINGS
#include "DxLib.h"
#include "MenuArea.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	SetGraphMode(1280, 800, 32);
	SetWindowSize(1280, 800);

	if (ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK || DxLib_Init() == -1) return -1; //初期化処理
	MenuOn();

	return 0;
}

