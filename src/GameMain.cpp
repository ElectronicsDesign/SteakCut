#define _CRT_SECURE_NO_WARNINGS
#include "DxLib.h"
#include "SpidarMouse.h"
#pragma comment (lib, "SpidarMouse.lib")
#include "api.h"
#include "MenuArea.h"
#include "AreaCheck.h"
#include "Debug.h"
#include <stdio.h>


typedef enum {
	eScene_Load,
	eScene_Menu,
	eScene_Start,
	eScene_Exit,
	eScene_Standby,
} eScene;

//グローバル変数の定義
int counter = 0;
int steakX[3] = { 406, 648, 890 };
int steakY[3] = { 380, 380, 380 };
int SSX[3][2] = { {406,380},{648,380},{890,380} };
int AudioCounter = 0;
bool AudioPlay = false;
extern int table, image, imgBack, Handle, Handle1;
extern int MouseX, MouseY;
extern int imgmiddle[4];
extern bool DebugMode;
static int SoundCounter = 0;

extern int Scene;
extern int ASFont;

void ResetArea() {
	counter = 0;
	steakX[0] = 406;
	steakX[1] = 648;
	steakX[2] = 890;

	SSX[0][0] = 406;
	SSX[0][1] = 380;
	SSX[1][0] = 648;
	SSX[1][1] = 380;
	SSX[2][0] = 890;
	SSX[2][1] = 380;

	AudioCounter = 0;
	AudioPlay = false;
}

void StartSteak() {
	static int meatAll = LoadGraph("./img/meet_main.png");
	static int Base = LoadGraph("./img/Main.png");
	static int meatX = -298;
	static int BaseX = -300;

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		if (BaseX >= 650 || (CheckHitKey(KEY_INPUT_S) != 0)) {
			meatX = -298;
			BaseX = -300;
			break;
		}
		if (meatX <= 648) {
			meatX += 10;
		}
		BaseX += 10;

		DrawRotaGraph(360, 300, 1.0, 0.0, table, TRUE);
		DrawRotaGraph(BaseX, 450, 1.0, 0.0, Base, TRUE);
		DrawRotaGraph(meatX, 380, 0.9, 0.0, meatAll, TRUE);
		DrawStringToHandle(1120, 0, "Sキーで演出スキップ", GetColor(255, 255, 255), ASFont);
	}
}

void AppStart() {
	SetMouseDispFlag(TRUE);

	//音量変更
	ChangeVolumeSoundMem(255 * 30 / 100, Handle);
	ChangeVolumeSoundMem(255 * 50 / 100, Handle1);

	StartSteak();

	while (!ProcessMessage() && !ClearDrawScreen()) {
		//↑メッセージ処理 ↑画面をクリア

		if (CheckHitKey(KEY_INPUT_R) != 0) { ResetArea(); }

		if (CheckHitKey(KEY_INPUT_M) != 0) {

			if ((MessageBox(NULL, TEXT("タイトル画面に戻りますか?"),
				TEXT("SteakCut"), MB_YESNO | MB_ICONQUESTION)) == IDYES) {
				StopSoundMem(Handle);
				StopSoundMem(Handle1);
				ResetArea();
				Scene = eScene_Menu;
				Sleep(1 * 200);
				break;
			}

		}

		GetMousePoint(&MouseX, &MouseY);

		if (AntiMem() == true && DebugMode == false) {
			MessageBox(NULL, "[ERROR:0003]\n\n不正な操作を検出したため終了します。", "MW-Secure AntiCheat", MB_OK | MB_ICONSTOP);
			CloseSpidarMouse();

			exit(2);
		}

		//各種画像の読み込み
		DrawRotaGraph(360, 300, 1.0, 0.0, table, TRUE);
		DrawRotaGraph(650, 450, 1.0, 0.0, imgBack, TRUE);
		DrawRotaGraph(steakX[0], steakY[0], 0.9, 0.0, imgmiddle[0], TRUE);
		DrawRotaGraph(steakX[1], steakY[1], 0.9, 0.0, imgmiddle[1], TRUE);
		DrawRotaGraph(steakX[2], steakY[2], 0.9, 0.0, imgmiddle[2], TRUE);
		DrawRotaGraph(MouseX, MouseY, 0.6, 0.0, image, TRUE);

		if (steakX[0] >= 404) {
			DrawStringToHandle(480, 210, "切ってみよう!", GetColor(255, 255, 0), ASFont);
			DrawTriangleAA(520, 230, 530, 230, 525, 235, GetColor(255, 255, 0), TRUE);
		}

		if (steakX[2] <= 892) {
			DrawStringToHandle(725, 210, "切ってみよう!", GetColor(255, 255, 0), ASFont);
			DrawTriangleAA(765, 230, 775, 230, 770, 235, GetColor(255, 255, 0), TRUE);
		}

		DrawStringToHandle(1155, 0, "Rキーでリセット", GetColor(255, 255, 255), ASFont);
		DrawStringToHandle(970, 0, "Mキーでタイトルに戻る", GetColor(255, 255, 255), ASFont);

		if ((steakX[0] <= 380) || (steakX[2] >= 915)) {
			DrawStringToHandle(0, 0, "これ以上切ることはできません。Rキーを押してリセットして下さい。", GetColor(255, 255, 0), ASFont);
		}
		else {
			AreaCheck(550, 505, 420, 310, 0, true);		//左の肉を動かすかチェック
			AreaCheck(805, 745, 420, 310, 2, false);	//右の肉を動かすかチェック
		}

		//デバッグ用
		if (DebugMode == true) {
			OutXYData();
			PicArea();
			FPSPrint();
			FlagControl();
		}

		ScreenFlip();//裏画面を表画面に反映

		//10秒の音源のため10秒に1回再生
		if (SoundCounter % 600 == 0) {
			PlaySoundMem(Handle, DX_PLAYTYPE_BACK, FALSE); // 効果音を再生する
		}
		AudioCheck();	//マウス動作後の効果音再生状態チェック


	}
}