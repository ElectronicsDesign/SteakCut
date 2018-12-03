# define _CRT_SECURE_NO_WARNINGS
#include "DxLib.h"


char Key[256];

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	if (ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK || DxLib_Init() == -1) return -1; //初期化処理

	int image = LoadGraph("./img/Knife_a.png");
	int imgBack = LoadGraph("./img/Main.png");
	int Handle = LoadSoundMem("./snd/Start.mp3");
	int Handle1 = LoadSoundMem("./snd/Center.mp3");
	int imgmiddle[4];
	int counter = 0;

	int steakX[4] = { 180, 304, 428 };
	int steakY[4] = { 200, 200, 200 };


	//画像を分割してロード
	LoadDivGraph("./img/meet_main.png", 3, 3, 1, 268, 412, imgmiddle);

	char StrBuf[128], StrBuf2[32];
	int MouseX, MouseY;
	int StringCr, BoxCr;

	if (DxLib_Init() == -1)    // ＤＸライブラリ初期化処理
	{
		return -1;    // エラーが起きたら直ちに終了
	}

	SetMouseDispFlag(TRUE);
	StringCr = GetColor(255, 255, 255);

	BoxCr = GetColor(0, 0, 0);

	ChangeVolumeSoundMem(255 * 30/100, Handle);
	ChangeVolumeSoundMem(255 * 50/ 100, Handle1);


	while (!ProcessMessage() && !ClearDrawScreen() && !GetHitKeyStateAll(Key) && !Key[KEY_INPUT_ESCAPE]) {
		//↑メッセージ処理 ↑画面をクリア ↑キーボード入力状態取得 ↑ESCが押されていない

		int x, y;
		int Mouse = GetMouseInput();
		GetMousePoint(&x, &y);
		GetMousePoint(&MouseX, &MouseY);

		DrawRotaGraph(300, 250, 0.5, 0.0, imgBack, TRUE);

		DrawRotaGraph(steakX[0], steakY[0], 0.46, 0.0, imgmiddle[0], TRUE);
		DrawRotaGraph(steakX[1], steakY[1], 0.46, 0.0, imgmiddle[1], TRUE);
		DrawRotaGraph(steakX[2], steakY[2], 0.46, 0.0, imgmiddle[2], TRUE);

		DrawRotaGraph(x, y, 0.5, 0.0, image, TRUE);


		ScreenFlip();//裏画面を表画面に反映



		lstrcpy(StrBuf, "座標X"); // 文字列"座標 Ｘ"をStrBufにコピー	
		_itoa(MouseX, StrBuf2, 10); // MouseXの値を文字列にしてStrBuf2に格納
		lstrcat(StrBuf, StrBuf2); // StrBufの内容にStrBuf2の内容を付け足す
		lstrcat(StrBuf, " Y "); // StrBufの内容に文字列"Ｙ"を付け足す
		_itoa(MouseY, StrBuf2, 10); // MouseYの値を文字列にしてStrBuf2に格納
		lstrcat(StrBuf, StrBuf2); // StrBufの内容にStrBuf2の内容を付け足す

		DrawBox(0, 0, 200, 32, BoxCr, TRUE);

		DrawString(0, 0, StrBuf, StringCr);
		DrawFormatString(0, 20, 0xffffff, "%d", image);
		DrawFormatString(0, 40, 0xffffff, "%d", imgBack);
		DrawFormatString(0, 60, 0xffffff, "%d", Handle);


		if ((Mouse & MOUSE_INPUT_LEFT)!=0){
			PlaySoundMem(Handle1, DX_PLAYTYPE_BACK, FALSE); // 効果音を再生する
		}
		else {
			PlaySoundMem(Handle, DX_PLAYTYPE_BACK, FALSE); // 効果音を再生する
		}

		if ((MouseX > 129) && (MouseX < 516)) {
			if ((MouseY > 150) && (MouseY < 200)) {
				counter++;
				if (counter == 30) {
					steakX[0]--;
					counter = 0;
				}
			}
		}

		if ((MouseY > 150) && (MouseY < 220)) {
			if ((MouseX > 129) && (MouseX < 496)) {
				counter++;
				if (counter == 30) {
					steakX[0]--;
					counter = 0;
				}
			}
		}

	}

	DxLib_End();
	return 0;
}

