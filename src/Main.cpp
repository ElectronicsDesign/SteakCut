#define _CRT_SECURE_NO_WARNINGS
#include "DxLib.h"
#include "MenuArea.h"
#include "api.h"
#include<Windows.h>
#include<math.h>
#define PI 3.141592653589793238462643383279502884197169399375105820974944592307810679
#include<SpiderMouce.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	SetGraphMode(1280, 800, 32);
	SetWindowSize(1280, 800);

	if (ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK || DxLib_Init() == -1) return -1; //初期化処理
	MenuOn();

	ConnectDevice();

	for (int i = 0; i < 360 * 3; i++) {
		float theta = PI*i / 180.0;
		OutPower(sin(theta), cos(theta), 10);
		Sleep(5);
	}

	return 0;
}

