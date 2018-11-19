# define _CRT_SECURE_NO_WARNINGS
#include "DxLib.h"


char Key[256];

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	if (ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK || DxLib_Init() == -1) return -1; //初期化処理

	int image = LoadGraph("./img/Knife_a.png");
	int imgBack = LoadGraph("./img/Main.png");
	int imgmiddle = LoadGraph("./img/meet_main.png");
	int imgmiddle3 = LoadGraph("./img/meet_g2.png");
	int imgmiddle4 = LoadGraph("./img/meet_g3.png");
	int imgmiddle5 = LoadGraph("./img/meet_g1.png");

	char StrBuf[128], StrBuf2[32];
	int MouseX, MouseY;
	int StringCr, BoxCr;

	if (DxLib_Init() == -1)    // ＤＸライブラリ初期化処理
	{
		return -1;    // エラーが起きたら直ちに終了
	}

	//int Mouse = GetMouseInput();
	int Handle = LoadSoundMem("./snd/Start.mp3");
	int Handle1 = LoadSoundMem("./snd/Center.mp3");



	SetMouseDispFlag(TRUE);
	StringCr = GetColor(255, 255, 255);

	BoxCr = GetColor(0, 0, 0);

	ChangeVolumeSoundMem(0 * 30/100, Handle);
	ChangeVolumeSoundMem(0 * 50/ 100, Handle1);


	while (!ProcessMessage() && !ClearDrawScreen() && !GetHitKeyStateAll(Key) && !Key[KEY_INPUT_ESCAPE]) {
		//↑メッセージ処理 ↑画面をクリア ↑キーボード入力状態取得 ↑ESCが押されていない

		int x, y;
		int Mouse = GetMouseInput();
		GetMousePoint(&x, &y);
		GetMousePoint(&MouseX, &MouseY);

		DrawRotaGraph(300, 250, 0.5, 0.0, imgBack, TRUE);

		if ((Mouse & MOUSE_INPUT_LEFT) != 0) {
			DrawRotaGraph(450, 200, 0.2, 0.0, imgmiddle3, TRUE);
			DrawRotaGraph(350, 200, 0.2, 0.0, imgmiddle4, TRUE);
			DrawRotaGraph(145, 200, 0.2, 0.0, imgmiddle5, TRUE);
		}
		else {
			DrawRotaGraph(300, 200, 0.5, 0.0, imgmiddle, TRUE);
		}
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

		


	

	}

	DxLib_End();
	return 0;
}

