#define _CRT_SECURE_NO_WARNINGS
#include "DxLib.h"

static int DMouseX, DMouseY;
extern int ASFont;
extern int steakX[4];
extern bool DeviceStatus;

float FPS = 0.0;
int  FPSTime[2] = { 0, }, FPSTime_i = 0;
char Str[256];
char buf[256];


//デバッグ用関数

//マウスのXY座標表示関数
void OutXYData() {
	GetMousePoint(&DMouseX, &DMouseY);
	DrawStringToHandle(1100, 20, "DEBUG", GetColor(255, 255, 255), ASFont);
	DrawStringToHandle(1210, 20, "X", GetColor(255, 255, 255), ASFont);
	DrawStringToHandle(1210, 40, "Y", GetColor(255, 255, 255), ASFont);

	sprintf(buf, "%d", DMouseX);
	DrawStringToHandle(1230, 20, buf, GetColor(255, 255, 255), ASFont);
	sprintf(buf, "%d", DMouseY);
	DrawStringToHandle(1230, 40, buf, GetColor(255, 255, 255), ASFont);

}

//画像の始点座標表示関数
void PicArea() {
	DrawStringToHandle(1170, 80, "Steak0", GetColor(255, 255, 255), ASFont);
	DrawStringToHandle(1170, 100, "Steak1", GetColor(255, 255, 255), ASFont);
	DrawStringToHandle(1170, 120, "Steak2", GetColor(255, 255, 255), ASFont);

	sprintf(buf, "%d", steakX[0]);
	DrawStringToHandle(1230, 80, buf, GetColor(255, 255, 255), ASFont);
	sprintf(buf, "%d", steakX[1]);
	DrawStringToHandle(1230, 100, buf, GetColor(255, 255, 255), ASFont);
	sprintf(buf, "%d", steakX[2]);
	DrawStringToHandle(1230, 120, buf, GetColor(255, 255, 255), ASFont);
}

//フレームレート表示関数
void FPSPrint() {

	if (FPSTime_i == 0)
		FPSTime[0] = GetNowCount();
	if (FPSTime_i == 49) {
		FPSTime[1] = GetNowCount();
		FPS = 1000.0f / ((FPSTime[1] - FPSTime[0]) / 50.0f);
		FPSTime_i = 0;
	}
	else
		FPSTime_i++;
	if (FPS != 0)
		sprintf(Str, "%.2f", FPS);
	DrawStringToHandle(1195, 60, "FPS", GetColor(255, 255, 255), ASFont);
	DrawStringToHandle(1230, 60, Str, GetColor(255, 255, 255), ASFont);
	return;
}

//USBデバイス接続状態変更関数
void FlagControl() {
	if (CheckHitKey(KEY_INPUT_D) != 0) {
		if (DeviceStatus == true) {
			DeviceStatus = false;
			Sleep(1 * 100);
		}
		else {
			DeviceStatus = true;
			Sleep(1 * 100);
		}
	}
}
