#include "DxLib.h"
#include "api.h"
#include "GameMain.h"

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
	DrawStringToHandle(550, 500, "[X] Exit", GetColor(0, 0, 0), FontControl);

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
		DrawString(0, 60, "[ERROR : 0001] 画像の展開に失敗しました。正しくファイルが配置されているかご確認下さい。", GetColor(255, 255, 255));
		DrawString(0, 80, "何かキーを押すと終了します。", GetColor(255, 255, 255));
		WaitKey();
		ExitApp();
	}
}

void LoadCheckSnd() {
	if (Handle == -1 || Handle1 == -1) {
		DrawString(0, 80, "[ERROR : 0002] 音源の展開に失敗しました。正しくファイルが配置されているかご確認下さい。", GetColor(255, 255, 255));
		DrawString(0, 100, "何かキーを押すと終了します。", GetColor(255, 255, 255));
		WaitKey();
		ExitApp();
	}
}

void LoadMem() {
	DrawBoxAA(1100, 780, 1270, 795, GetColor(255, 255, 255), FALSE);


	DrawString(0, 0, "起動準備を開始...", GetColor(255, 255, 255));
	DrawBoxAA(1101, 781, 1120, 794, GetColor(0, 255, 65), TRUE);

	DrawString(0, 20, "フォント準備中...", GetColor(255, 255, 255));

	ASBFont = CreateFontToHandle(NULL, 20, 6, DX_FONTTYPE_ANTIALIASING_8X8);
	FontControl = CreateFontToHandle(NULL, 40, 4, DX_FONTTYPE_ANTIALIASING_8X8);
	ASFont = CreateFontToHandle(NULL, -1, -1, DX_FONTTYPE_ANTIALIASING_8X8);
	DrawBoxAA(1120, 781, 1150, 794, GetColor(0, 255, 65), TRUE);

	DrawString(0, 40, "画像をメモリに展開中...", GetColor(255, 255, 255));

	image = LoadGraph("./img/Knife_a.png");
	imgBack = LoadGraph("./img/Main.png");
	LoadDivGraph("./img/meet_main.png", 3, 3, 1, 268, 412, imgmiddle);
	Background = LoadGraph("./img/MenuMain.jpg");
	logo = LoadGraph("./img/logo.png");
	DrawBoxAA(1150, 781, 1220, 794, GetColor(0, 255, 65), TRUE);

	LoadCheckImg();
	DrawBoxAA(1220, 781, 1230, 794, GetColor(0, 255, 65), TRUE);

	DrawString(0, 60, "音源をメモリに展開中...", GetColor(255, 255, 255));

	Handle = LoadSoundMem("./snd/Start.mp3");
	Handle1 = LoadSoundMem("./snd/Center.mp3");
	DrawBoxAA(1230, 781, 1250, 794, GetColor(0, 255, 65), TRUE);

	LoadCheckSnd();
	DrawBoxAA(1250, 781, 1260, 794, GetColor(0, 255, 65), TRUE);

	DrawString(0, 80, "デバイスの接続検証中...", GetColor(255, 255, 255));
	ConnectStatus();
	DrawBoxAA(1260, 781, 1269, 794, GetColor(0, 255, 65), TRUE);

	MenuOn();
}