# define _CRT_SECURE_NO_WARNINGS
#include "DxLib.h"


char Key[256];

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	if (ChangeWindowMode(FALSE) != DX_CHANGESCREEN_OK || DxLib_Init() == -1) return -1; //初期化処理

	int image = LoadGraph("./img/Knife_a.png");
	int imgBack = LoadGraph("./img/Main.png");
	int imgmiddle = LoadGraph("./img/meet_main.png");

	char StrBuf[128], StrBuf2[32];
	int MouseX, MouseY;
	int StringCr, BoxCr;

	if (DxLib_Init() == -1)    // ＤＸライブラリ初期化処理
	{
		return -1;    // エラーが起きたら直ちに終了
	}

	int Mouse = GetMouseInput();
	int Handle = LoadSoundMem("kitchen-knife-cut3.mp3");

	SetMouseDispFlag(TRUE);
	StringCr = GetColor(255, 255, 255);

	BoxCr = GetColor(0, 0, 0);



	while (!ProcessMessage() && !ClearDrawScreen() && !GetHitKeyStateAll(Key) && !Key[KEY_INPUT_ESCAPE]) {
		//↑メッセージ処理 ↑画面をクリア ↑キーボード入力状態取得 ↑ESCが押されていない

		int x, y;
		GetMousePoint(&x, &y);
		GetMousePoint(&MouseX, &MouseY);

		DrawRotaGraph(300, 250, 0.5, 0.0, imgBack, TRUE);
		DrawRotaGraph(300, 200, 0.5, 0.0, imgmiddle, TRUE);
		DrawRotaGraph(x, y, 0.5, 0.0, image, TRUE);


		ScreenFlip();//裏画面を表画面に反映

		lstrcpy(StrBuf, "座標 Ｘ"); // 文字列"座標 Ｘ"をStrBufにコピー	
		_itoa(MouseX, StrBuf2, 10); // MouseXの値を文字列にしてStrBuf2に格納
		lstrcat(StrBuf, StrBuf2); // StrBufの内容にStrBuf2の内容を付け足す
		lstrcat(StrBuf, "　Ｙ "); // StrBufの内容に文字列"Ｙ"を付け足す
		_itoa(MouseY, StrBuf2, 10); // MouseYの値を文字列にしてStrBuf2に格納
		lstrcat(StrBuf, StrBuf2); // StrBufの内容にStrBuf2の内容を付け足す

		DrawBox(0, 0, 200, 32, BoxCr, TRUE);

		DrawString(0, 0, StrBuf, StringCr);
		DrawFormatString(0, 20,0xffffff,"%d",image);
		DrawFormatString(0, 40, 0xffffff, "%d", imgBack);

		if (Mouse & MOUSE_INPUT_RIGHT) {
			PlaySoundMem(Handle, DX_PLAYTYPE_BACK); // 効果音を再生する
		}

	}

	DxLib_End();
	return 0;
}
