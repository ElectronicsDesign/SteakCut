#include "DxLib.h"
#include "GameMain.h"

typedef enum {
	eScene_Menu,
	eScene_Start,
	eScene_Exit,
} eScene;

int Scene = eScene_Menu;
int ASFont;
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
	//一度だけメモリにロード(メモリリーク防止)
	if (loadStatus == false) {
		FontControl = CreateFontToHandle(NULL, 40, 4, DX_FONTTYPE_ANTIALIASING_8X8);
		ASFont = CreateFontToHandle(NULL, -1, -1, DX_FONTTYPE_ANTIALIASING_8X8);
		Background = LoadGraph("./img/MenuMain.jpg");
		logo = LoadGraph("./img/logo.png");
		loadStatus = true;
	}
	
	DrawRotaGraph(640, 400, 1.0, 0.0, Background, TRUE);
	DrawRotaGraph(640, 180, 1.4, 0.0, logo, TRUE);

	DrawStringToHandle(550, 450, "[S] Start", GetColor(0, 0, 0), FontControl);
	DrawStringToHandle(550, 500, "[X] Exit", GetColor(0, 0, 0), FontControl);

	DrawStringToHandle(5, 780, "Developed by ElectronicsDesign Group2", GetColor(0, 0, 0), ASFont);
	DrawStringToHandle(1210, 780, "Ver 1.4", GetColor(0, 0, 0), ASFont);

}

void StartApp() {

	AppStart();
}

void ExitApp() {
	DxLib_End();
	exit(0);
}

void MenuOn(){

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