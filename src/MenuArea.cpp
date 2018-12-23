#include "DxLib.h"
#include "Debug.h"
#include "SpidarMouse.h"
#include "api.h"
#include "GameMain.h"
#pragma comment (lib, "SpidarMouse.lib")

typedef enum {
	eScene_Load,
	eScene_Menu,
	eScene_Start,
	eScene_Exit,
	eScene_DeviceTool,
	eScene_Standby,
} eScene;

int Scene;
int ASFont;
int ASBFont;
int image, imgBack, Handle, Handle1;
int imgmiddle[4];
int MouseX, MouseY;
int pointer = 0;
bool DeviceStatus = false;
static int FontControl;
static int Background;
static int logo;
static bool loadStatus = false;

void UpdateScene() {
	if (CheckHitKey(KEY_INPUT_R) != 0) {
		if (OpenSpidarMouse() == 1) {
			MessageBox(NULL, "USBデバイスの接続に成功しました。", "EteakCut Device Controller", MB_OK);
			DeviceStatus = true;
		}
		else {
			MessageBox(NULL, "[WARN : 0001]\n\nUSBデバイスとの接続に失敗しました。\n正しくデバイスが接続されているかご確認下さい。", "EteakCut Device Controller", MB_OK);
		}
	}
}

void OutTitle() {
	DrawRotaGraph(640, 400, 1.0, 0.0, Background, TRUE);
	DrawRotaGraph(640, 180, 1.0, 0.0, logo, TRUE);

	DrawStringToHandle(3, 4, "USBデバイス : ", GetColor(0, 0, 0), ASBFont);

	if (DeviceStatus == true) {
		DrawCircleAA(150, 13, 9, 180, GetColor(0, 255, 65), 1);
		DrawStringToHandle(165, 4, "接続済み (ONLINE)", GetColor(0, 255, 65), ASBFont);

	}
	else {
		DrawCircleAA(150, 13, 9, 180, GetColor(248, 6, 6), 1);
		DrawStringToHandle(165, 4, "未接続 (OFFLINE)", GetColor(248, 6, 6), ASBFont);
	}

	if (pointer == 0) {
		DrawStringToHandle(430, 450, "→", GetColor(0, 0, 0), FontControl);
	}
	else if (pointer == 1) {
		DrawStringToHandle(430, 500, "→", GetColor(0, 0, 0), FontControl);
	}
	else if (pointer == 2) {
		DrawStringToHandle(430, 550, "→", GetColor(0, 0, 0), FontControl);

	}

	DrawStringToHandle(5, 780, "Developed by ElectronicsDesign Group2", GetColor(0, 0, 0), ASFont);
	DrawStringToHandle(1210, 780, "Ver 1.7", GetColor(0, 0, 0), ASFont);
}

void Menu() {
	OutTitle();

	DrawStringToHandle(480, 450, "スタート", GetColor(0, 0, 0), FontControl);
	DrawStringToHandle(480, 500, "デバイス管理", GetColor(0, 0, 0), FontControl);
	DrawStringToHandle(480, 550, "終了", GetColor(0, 0, 0), FontControl);

	if (CheckHitKey(KEY_INPUT_RETURN) != 0) {
		if (pointer == 0) {
			Scene = eScene_Standby;
		}
		else if (pointer == 1) {
			Sleep(1 * 100);
			pointer = 0;
			Scene = eScene_DeviceTool;
		}
		else if (pointer == 2) {
			Scene = eScene_Exit;

		}
	}

	if ((CheckHitKey(KEY_INPUT_UP) != 0)) {
		if (pointer == 0) {
			pointer = 2;
		}
		else {
			pointer--;
		}
		Sleep(1 * 100);
	}

	if ((CheckHitKey(KEY_INPUT_DOWN) != 0)) {
		if (pointer == 2) {
			pointer = 0;
		}
		else {
			pointer++;
		}
		Sleep(1 * 100);
	}

}

void DeviceTool() {
	OutTitle();

	if (DeviceStatus == true) {
		DrawStringToHandle(480, 450, "USBデバイスを接続解除", GetColor(0, 0, 0), FontControl);
		DrawStringToHandle(480, 500, "モーターの動作確認", GetColor(0, 0, 0), FontControl);
	}
	else {
		DrawStringToHandle(480, 450, "USBデバイスと接続", GetColor(0, 0, 0), FontControl);

	}

	DrawStringToHandle(480, 550, "メニュー画面へ", GetColor(0, 0, 0), FontControl);


	if (CheckHitKey(KEY_INPUT_RETURN) != 0) {
		if (pointer == 0) {
			if (DeviceStatus == true) {
				CloseSpidarMouse();
				MessageBox(NULL, "USBデバイスとの接続を解除しました。", "EteakCut Device Controller", MB_OK);
				DeviceStatus = false;
			}
			else {
				if (OpenSpidarMouse() == 1) {
					MessageBox(NULL, "USBデバイスに接続完了しました。", "EteakCut Device Controller", MB_OK);
					DeviceStatus = true;
				}
				else {
					MessageBox(NULL, "[WARN : 0002]\n\nUSBデバイスとの接続に失敗しました。\nUSBデバイスが正しく接続されているかご確認下さい。", "EteakCut Device Controller", MB_OK);
				}
			}
			Sleep(1 * 100);
		}
		else if (pointer == 1) {

		}
		else if (pointer == 2) {
			pointer = 0;
			Scene = eScene_Menu;
			Sleep(1 * 100);

		}
	}

	if ((CheckHitKey(KEY_INPUT_UP) != 0)) {
		if (pointer == 0) {
			pointer = 2;
		}
		else {
			if (DeviceStatus == true) {
				pointer--;
			}
			else {
				if (pointer == 2) {
					pointer = 0;
				}
			}
		}
		Sleep(1 * 100);
	}

	if ((CheckHitKey(KEY_INPUT_DOWN) != 0)) {
		if (pointer == 2) {
			pointer = 0;
		}
		else {
			if (DeviceStatus == true) {
				pointer++;
			}
			else {
				if (pointer == 0) {
					pointer = 2;
				}
			}
		}
		Sleep(1 * 100);
	}

}

void Standby() {
	int counter = 0;
	DrawLineAA(650, 0, 650, 800, GetColor(0, 255, 65));
	DrawLineAA(0, 350, 1280, 350, GetColor(0, 255, 65));
	DrawCircleAA(650, 350, 5, 180, GetColor(0, 255, 65), 1);

	DrawStringToHandle(0, 0, "初期位置の設定を行います。", GetColor(255, 255, 0), ASFont);
	DrawStringToHandle(0, 18, "丸の部分にマウスを置いてクリックして下さい。Mキーを押すとメニューに戻れます。", GetColor(255, 255, 0), ASFont);
	while (ProcessMessage() == 0) {
		if (CheckHitKey(KEY_INPUT_M) == 1) {
			Scene = eScene_Menu;
			break;
		}

		GetMousePoint(&MouseX, &MouseY);
		if (((MouseX >= 645) && (MouseX <= 655)) && ((MouseY >= 345) && (MouseY <= 355)) && ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)) {
			Scene = eScene_Start;
			break;
		}
	}

}

void StartApp() {
	AppStart();
}

void ExitApp() {
	CloseSpidarMouse();
	DxLib_End();
	exit(0);
}

void MenuOn() {
	Scene = eScene_Menu;
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		switch (Scene) {
			case eScene_Standby:
				Standby();
				break;
			case eScene_Menu:
				Menu();
				break;
			case eScene_Start:
				StartApp();
				break;
			case eScene_Exit:
				ExitApp();
				break;
			case eScene_DeviceTool:
				DeviceTool();
				break;
		}
		if (Scene != eScene_DeviceTool) {

		}
		else {
			UpdateScene();
		}
	}
}

void LoadCheckImg() {
	if (image == -1 || imgBack == -1 || Background == -1 || logo == -1 || imgmiddle[0] == -1) {
		MessageBox(NULL, "[ERROR : 0001]\n\n画像の展開に失敗しました。\n正しくファイルが配置されているかご確認下さい。", "EteakCut Load Error", MB_OK);
		ExitApp();
	}
}

void LoadCheckSnd() {
	if (Handle == -1 || Handle1 == -1) {
		MessageBox(NULL, "[ERROR : 0002]\n\n音源の展開に失敗しました。\n正しくファイルが配置されているかご確認下さい。", "EteakCut Load Error", MB_OK);
		ExitApp();
	}
}

void LoadMem() {
	ScreenFlip();
	Sleep(5 * 100);
	DrawBoxAA(551, 481, 571, 494, GetColor(0, 255, 65), TRUE);

	ASBFont = CreateFontToHandle(NULL, 20, 6, DX_FONTTYPE_ANTIALIASING_8X8);
	FontControl = CreateFontToHandle(NULL, 40, 4, DX_FONTTYPE_ANTIALIASING_8X8);
	ASFont = CreateFontToHandle(NULL, -1, -1, DX_FONTTYPE_ANTIALIASING_8X8);
	DrawBoxAA(570, 481, 590, 494, GetColor(0, 255, 65), TRUE);
	ScreenFlip();

	image = LoadGraph("./img/Knife_a.png");
	imgBack = LoadGraph("./img/Main.png");
	LoadDivGraph("./img/meet_main.png", 3, 3, 1, 268, 412, imgmiddle);
	Background = LoadGraph("./img/MenuMain.jpg");
	logo = LoadGraph("./img/logo.png");
	DrawBoxAA(590, 481, 610, 494, GetColor(0, 255, 65), TRUE);

	LoadCheckImg();
	DrawBoxAA(610, 481, 630, 494, GetColor(0, 255, 65), TRUE);
	ScreenFlip();

	Handle = LoadSoundMem("./snd/Start.mp3");
	Handle1 = LoadSoundMem("./snd/Center.mp3");
	DrawBoxAA(630, 481, 650, 494, GetColor(0, 255, 65), TRUE);

	LoadCheckSnd();
	DrawBoxAA(650, 481, 660, 494, GetColor(0, 255, 65), TRUE);
	ScreenFlip();

	if (OpenSpidarMouse() == 1) {
		DeviceStatus = true;
	}
	else {
		MessageBox(NULL, "[WARN : 0001]\n\nUSBデバイスとの接続に失敗しました。オフラインモードで起動します。\n(デバイスとの再接続はデバイス管理で行えます。)", "EteakCut Device Controller", MB_OK);
		Sleep(1 * 100);
	}

	DrawBoxAA(660, 481, 719, 494, GetColor(0, 255, 65), TRUE);
}