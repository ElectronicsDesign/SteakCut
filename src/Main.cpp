#define _CRT_SECURE_NO_WARNINGS
#include "DxLib.h"
#include "MenuArea.h"

bool DebugMode = false;

//起動時に実行(main関数)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	SetGraphMode(1280, 800, 32);	//描画設定を1280 x 800, 32bitカラーに設定
	SetWindowSize(1280, 800);	//ウィンドウサイズを1280 x 800に設定
	SetMainWindowText("SteakCut");	//アプリケーションタイトルをSteakCutに設定
	SetWindowIconID(101);

	if (ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK || DxLib_Init() == -1) return -1;

	if ((LoadGraphScreen(240, 220, "./img/Devlogo.png", TRUE)) == -1) {
		MessageBox(NULL, "[ERROR : 0000]\n\nファイルが不整合です。再ダウンロードしてください。", "EteakCut Start Error", MB_OK | MB_ICONERROR);
		exit(9);
	}
	DrawString(450, 480, "起動中 :", GetColor(255, 255, 255));
	DrawBoxAA(550, 480, 720, 495, GetColor(255, 255, 255), FALSE);
	LoadGraphScreen(460, 620, "./img/shift.png", TRUE);
	DrawString(550, 632, "Press Shift to Debug Mode", GetColor(255, 255, 255));

	LoadMem();	//画像、音源をメモリに展開開始
	MenuOn();	//タイトル画面へ遷移

	return 0;
}
