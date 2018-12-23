#define _CRT_SECURE_NO_WARNINGS
#include "DxLib.h"

extern int ASFont;
extern int MouseX, MouseY;
extern int steakX[4];

float FPS = 0.0;
int  FPSTime[2] = { 0, }, FPSTime_i = 0;
char Str[256];
char buf[256];


void OutXYData() {
	GetMousePoint(&MouseX, &MouseY);
	DrawStringToHandle(1100, 20, "DEBUG", GetColor(255, 255, 255), ASFont);
	DrawStringToHandle(1210, 20, "X", GetColor(255, 255, 255), ASFont);
	DrawStringToHandle(1210, 40, "Y", GetColor(255, 255, 255), ASFont);
	DrawStringToHandle(1170, 80, "Steak0", GetColor(255, 255, 255), ASFont);
	DrawStringToHandle(1170, 100, "Steak1", GetColor(255, 255, 255), ASFont);
	DrawStringToHandle(1170, 120, "Steak2", GetColor(255, 255, 255), ASFont);

	sprintf(buf, "%d", MouseX);
	DrawStringToHandle(1230, 20, buf, GetColor(255, 255, 255), ASFont);
	sprintf(buf, "%d", MouseY);
	DrawStringToHandle(1230, 40, buf, GetColor(255, 255, 255), ASFont);

	sprintf(buf, "%d", steakX[0]);
	DrawStringToHandle(1230, 80, buf, GetColor(255, 255, 255), ASFont);
	sprintf(buf, "%d", steakX[1]);
	DrawStringToHandle(1230, 100, buf, GetColor(255, 255, 255), ASFont);
	sprintf(buf, "%d", steakX[2]);
	DrawStringToHandle(1230, 120, buf, GetColor(255, 255, 255), ASFont);
}

void FPSPrint() {

	if (FPSTime_i == 0)
		FPSTime[0] = GetNowCount();               //1周目の時間取得
	if (FPSTime_i == 49) {
		FPSTime[1] = GetNowCount();               //50周目の時間取得
		FPS = 1000.0f / ((FPSTime[1] - FPSTime[0]) / 50.0f);//測定した値からfpsを計算
		FPSTime_i = 0;//カウントを初期化
	}
	else
		FPSTime_i++;//現在何周目かカウント
	if (FPS != 0)
		sprintf(Str, "%.2f", FPS);
		DrawStringToHandle(1195, 60, "FPS", GetColor(255, 255, 255), ASFont);
		DrawStringToHandle(1230, 60, Str, GetColor(255, 255, 255), ASFont);
	return;
}