#include "DxLib.h"
#include "api.h"
#include "GameMain.h"

typedef enum {
	eScene_Load,
	eScene_Menu,
	eScene_Start,
	eScene_Exit,
} eScene;

int Scene;
int ASFont;
int ASBFont;
int image, imgBack, Handle, Handle1;
int imgmiddle[4];
bool DeviceStatus = false;
static int FontControl;
static int Background;
static int logo;
static bool loadStatus = false;

void UpdateScene() {

	if (CheckHitKey(KEY_INPUT_S) != 0) {
		Scene = eScene_Start;
	}
	if (CheckHitKey(KEY_INPUT_X) != 0) {
		Scene = eScene_Exit;
	}
}

void Menu() {
	DrawRotaGraph(640, 400, 1.0, 0.0, Background, TRUE);
	DrawRotaGraph(640, 180, 1.0, 0.0, logo, TRUE);

	DrawStringToHandle(3, 4, "USB�f�o�C�X : ", GetColor(0, 0, 0), ASBFont);

	if (DeviceStatus == true) {
		DrawCircleAA(150, 13, 9, 180, GetColor(0, 255, 65), 1);
		DrawStringToHandle(165, 4, "�ڑ��ς� (ONLINE)", GetColor(0, 255, 65), ASBFont);

	}
	else {
		DrawCircleAA(150, 13, 9, 180, GetColor(248, 6, 6), 1);
		DrawStringToHandle(165, 4, "���ڑ� (OFFLINE)", GetColor(248, 6, 6), ASBFont);
	}

	DrawStringToHandle(550, 450, "[S] Start", GetColor(0, 0, 0), FontControl);
	DrawStringToHandle(550, 500, "[X] Exit", GetColor(0, 0, 0), FontControl);

	DrawStringToHandle(5, 780, "Developed by ElectronicsDesign Group2", GetColor(0, 0, 0), ASFont);
	DrawStringToHandle(1210, 780, "Ver 1.5", GetColor(0, 0, 0), ASFont);

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
		DrawString(0, 60, "[ERROR : 0001] �摜�̓W�J�Ɏ��s���܂����B�������t�@�C�����z�u����Ă��邩���m�F�������B", GetColor(255, 255, 255));
		DrawString(0, 80, "�����L�[�������ƏI�����܂��B", GetColor(255, 255, 255));
		while (CheckHitKeyAll() == 0){
			if (ProcessMessage() == -1){
				break;
			}
		}
		DxLib_End();
		exit(0);
	}
}

void LoadCheckSnd() {
	if (Handle == -1 || Handle1 == -1) {
		DrawString(0, 80, "[ERROR : 0002] �����̓W�J�Ɏ��s���܂����B�������t�@�C�����z�u����Ă��邩���m�F�������B", GetColor(255, 255, 255));
		DrawString(0, 100, "�����L�[�������ƏI�����܂��B", GetColor(255, 255, 255));
		while (CheckHitKeyAll() == 0) {
			if (ProcessMessage() == -1) {
				break;
			}
		}
		DxLib_End();
		exit(0);
	}
}

void LoadMem() {
	DrawString(0, 0, "�N��������...", GetColor(255, 255, 255));
	DrawString(0, 20, "�t�H���g������...", GetColor(255, 255, 255));

	ASBFont = CreateFontToHandle(NULL, 20, 6, DX_FONTTYPE_ANTIALIASING_8X8);
	FontControl = CreateFontToHandle(NULL, 40, 4, DX_FONTTYPE_ANTIALIASING_8X8);
	ASFont = CreateFontToHandle(NULL, -1, -1, DX_FONTTYPE_ANTIALIASING_8X8);

	DrawString(0, 40, "�摜���������ɓW�J��...", GetColor(255, 255, 255));
	image = LoadGraph("./img/Knife_a.png");
	imgBack = LoadGraph("./img/Main.png");
	LoadDivGraph("./img/meet_main.png", 3, 3, 1, 268, 412, imgmiddle);
	Background = LoadGraph("./img/MenuMain.jpg");
	logo = LoadGraph("./img/logo.png");

	LoadCheckImg();

	DrawString(0, 60, "�������������ɓW�J��...", GetColor(255, 255, 255));
	Handle = LoadSoundMem("./snd/Start.mp3");
	Handle1 = LoadSoundMem("./snd/Center.mp3");

	LoadCheckSnd();

	DrawString(0, 80, "�f�o�C�X�̐ڑ����ؒ�...", GetColor(255, 255, 255));
	ConnectStatus();

	MenuOn();
}