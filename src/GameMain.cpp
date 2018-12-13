#define _CRT_SECURE_NO_WARNINGS
#include "DxLib.h"
#include "MenuArea.h"
#include "AreaCheck.h"
#include "Debug.h"
#include <stdio.h>

//グローバル変数の定義
int counter = 0;
int steakX[4] = { 406, 648, 890 };
int steakY[4] = { 380, 380, 380 };
int MouseX, MouseY;
int Handle1;
int AudioCounter = 0;
bool AudioPlay = false;
static bool loadStatus = false;
static 	int image, imgBack, Handle;
static int imgmiddle[4];
static int SoundCounter = 0;
char Key[256];

extern int Scene;
extern int ASFont;

void AppStart() {
	if (loadStatus == false) {
		image = LoadGraph("./img/Knife_a.png");
		imgBack = LoadGraph("./img/Main.png");
		Handle = LoadSoundMem("./snd/Start.mp3");
		Handle1 = LoadSoundMem("./snd/Center.mp3");
		LoadDivGraph("./img/meet_main.png", 3, 3, 1, 268, 412, imgmiddle);

		loadStatus = true;
	}

	SetMouseDispFlag(TRUE);

	//音量変更
	ChangeVolumeSoundMem(255 * 30 / 100, Handle);
	ChangeVolumeSoundMem(255 * 50 / 100, Handle1);


	while (!ProcessMessage() && !ClearDrawScreen() && !GetHitKeyStateAll(Key) && !Key[KEY_INPUT_ESCAPE]) {
		//↑メッセージ処理 ↑画面をクリア ↑キーボード入力状態取得 ↑ESCが押されていない

		if (Key[KEY_INPUT_LSHIFT] || Key[KEY_INPUT_RSHIFT]) { ResetArea(); }
		if (Key[KEY_INPUT_M]) { 
			StopSoundMem(Handle);
			StopSoundMem(Handle1);
			ResetArea();
			MenuOn();
		}

		GetMousePoint(&MouseX, &MouseY);

		//各種画像の読み込み
		DrawRotaGraph(650, 450, 1.0, 0.0, imgBack, TRUE);
		DrawRotaGraph(steakX[0], steakY[0], 0.9, 0.0, imgmiddle[0], TRUE);
		DrawRotaGraph(steakX[1], steakY[1], 0.9, 0.0, imgmiddle[1], TRUE);
		DrawRotaGraph(steakX[2], steakY[2], 0.9, 0.0, imgmiddle[2], TRUE);
		DrawRotaGraph(MouseX, MouseY, 0.6, 0.0, image, TRUE);

		DrawStringToHandle(1120, 0, "Shiftキーでリセット", GetColor(255, 255, 255), ASFont);
		DrawStringToHandle(940, 0, "Mキーでタイトルに戻る", GetColor(255, 255, 255), ASFont);


		//デバッグ用
		OutXYData();
		FPSPrint();

		ScreenFlip();//裏画面を表画面に反映

		//10秒の音源のため10秒に1回再生
		if (SoundCounter % 600 == 0) {
			PlaySoundMem(Handle, DX_PLAYTYPE_BACK, FALSE); // 効果音を再生する
		}
		AudioCheck();	//マウス動作後の効果音再生状態チェック
		AreaCheck(550, 505, 420, 310, 0, true);		//左の肉を動かすかチェック
		AreaCheck(805, 745, 420, 310, 2, false);	//右の肉を動かすかチェック
	}

	DxLib_End();
}
