#include "DxLib.h"
#include "SpidarMouse.h"
#include "api.h"
#include "GameMain.h"
#pragma comment (lib, "SpidarMouse.lib")

typedef enum {
	eScene_Load,
	eScene_Menu,
	eScene_Start,
	eScene_Exit,
	eScene_Standby,
} eScene;

int Scene;
int ASFont;
int ASBFont;
int image, imgBack, Handle, Handle1;
int imgmiddle[4];
int MouseX, MouseY;
bool DeviceStatus = false;
static int FontControl;
static int Background;
static int logo;
static bool loadStatus = false;

void UpdateScene() {

	if (CheckHitKey(KEY_INPUT_S) != 0) {
		Scene = eScene_Standby;
	}
	if (CheckHitKey(KEY_INPUT_X) != 0) {
		Scene = eScene_Exit;
	}
}

void Menu() {
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

	DrawStringToHandle(550, 450, "[S] Start", GetColor(0, 0, 0), FontControl);
	DrawStringToHandle(550, 500, "[R] Device Tool", GetColor(0, 0, 0), FontControl);
	DrawStringToHandle(550, 550, "[X] Exit", GetColor(0, 0, 0), FontControl);

	DrawStringToHandle(5, 780, "Developed by ElectronicsDesign Group2", GetColor(0, 0, 0), ASFont);
	DrawStringToHandle(1210, 780, "Ver 1.6", GetColor(0, 0, 0), ASFont);

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
		}
		UpdateScene();
	}
}

void LoadCheckImg() {
	if (image == -1 || imgBack == -1 || Background == -1 || logo == -1 || imgmiddle[0] == -1) {
		MessageBox(NULL, "[ERROR : 0001] 画像の展開に失敗しました。正しくファイルが配置されているかご確認下さい。", "EteakCut Load Error", MB_OK);
		ExitApp();
	}
}

void LoadCheckSnd() {
	if (Handle == -1 || Handle1 == -1) {
		MessageBox(NULL, "[ERROR : 0002] 音源の展開に失敗しました。正しくファイルが配置されているかご確認下さい。", "EteakCut Load Error", MB_OK);
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
		MessageBox(NULL, "[WARN : 0001] SpiderMouseとの接続に失敗しました。正しくデバイスが接続されているかご確認下さい。", "EteakCut Device Controller", MB_OK);
	}

	DrawBoxAA(660, 481, 719, 494, GetColor(0, 255, 65), TRUE);
}