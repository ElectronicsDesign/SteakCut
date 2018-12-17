#define _CRT_SECURE_NO_WARNINGS
#include "DxLib.h"
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
extern int image, imgBack, Handle, Handle1;
extern int MouseX, MouseY;
extern int imgmiddle[4];
static int SoundCounter = 0;
char Key[256];

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

void AppStart() {
	SetMouseDispFlag(TRUE);

	//音量変更
	ChangeVolumeSoundMem(255 * 30 / 100, Handle);
	ChangeVolumeSoundMem(255 * 50 / 100, Handle1);


	while (!ProcessMessage() && !ClearDrawScreen() && !GetHitKeyStateAll(Key) && !Key[KEY_INPUT_ESCAPE]) {
		//↑メッセージ処理 ↑画面をクリア ↑キーボード入力状態取得 ↑ESCが押されていない

		if (Key[KEY_INPUT_R]) { ResetArea(); }

		if (Key[KEY_INPUT_M]) { 
			StopSoundMem(Handle);
			StopSoundMem(Handle1);
			ResetArea();
			Scene = eScene_Menu;
			break;
		}

		GetMousePoint(&MouseX, &MouseY);

		if (AntiMem() == true) {
			MessageBox(NULL, "不正な操作を検出したため終了します。[ERROR:0003 メモリの改ざん検知]", "MW-Secure AntiCheat", MB_OK);
			exit(2);
		}

		//各種画像の読み込み
		DrawRotaGraph(650, 450, 1.0, 0.0, imgBack, TRUE);
		DrawRotaGraph(steakX[0], steakY[0], 0.9, 0.0, imgmiddle[0], TRUE);
		DrawRotaGraph(steakX[1], steakY[1], 0.9, 0.0, imgmiddle[1], TRUE);
		DrawRotaGraph(steakX[2], steakY[2], 0.9, 0.0, imgmiddle[2], TRUE);
		DrawRotaGraph(MouseX, MouseY, 0.6, 0.0, image, TRUE);

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
		OutXYData();
		FPSPrint();

		ScreenFlip();//裏画面を表画面に反映

		//10秒の音源のため10秒に1回再生
		if (SoundCounter % 600 == 0) {
			PlaySoundMem(Handle, DX_PLAYTYPE_BACK, FALSE); // 効果音を再生する
		}
		AudioCheck();	//マウス動作後の効果音再生状態チェック


	}
}