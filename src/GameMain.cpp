#define _CRT_SECURE_NO_WARNINGS
#include "DxLib.h"
#include "MenuArea.h"
#include "AreaCheck.h"

//�O���[�o���ϐ��̒�`
int counter = 0;
int steakX[4] = { 406, 648, 890 };
int steakY[4] = { 380, 380, 380 };
int MouseX, MouseY;
int Handle1;
int AudioCounter = 0;
bool AudioPlay = false;
char Key[256];

extern int Scene;
extern int ASFont;

void AppStart() {

	int SoundCounter = 0;
	int image = LoadGraph("./img/Knife_a.png");
	int imgBack = LoadGraph("./img/Main.png");
	int Handle = LoadSoundMem("./snd/Start.mp3");
	int imgmiddle[4];

	//���ʑ傫�߂̏Ă�������
	Handle1 = LoadSoundMem("./snd/Center.mp3");

	//�摜�𕪊����ă��[�h
	LoadDivGraph("./img/meet_main.png", 3, 3, 1, 268, 412, imgmiddle);

	char StrBuf[128], StrBuf2[32];
	int StringCr, BoxCr;

	SetMouseDispFlag(TRUE);
	StringCr = GetColor(255, 255, 255);

	BoxCr = GetColor(0, 0, 0);

	//���ʕύX
	ChangeVolumeSoundMem(255 * 30 / 100, Handle);
	ChangeVolumeSoundMem(255 * 50 / 100, Handle1);

	while (!ProcessMessage() && !ClearDrawScreen() && !GetHitKeyStateAll(Key) && !Key[KEY_INPUT_ESCAPE]) {
		//�����b�Z�[�W���� ����ʂ��N���A ���L�[�{�[�h���͏�Ԏ擾 ��ESC��������Ă��Ȃ�

		if (Key[KEY_INPUT_LSHIFT] || Key[KEY_INPUT_RSHIFT]) { ResetArea(); }

		int x, y, m, n;
		int Mouse = GetMouseInput();
		GetMousePoint(&x, &y);
		GetMousePoint(&m, &n);
		GetMousePoint(&MouseX, &MouseY);

		//�e��摜�̓ǂݍ���
		DrawRotaGraph(650, 450, 1.0, 0.0, imgBack, TRUE);
		DrawRotaGraph(steakX[0], steakY[0], 0.9, 0.0, imgmiddle[0], TRUE);
		DrawRotaGraph(steakX[1], steakY[1], 0.9, 0.0, imgmiddle[1], TRUE);
		DrawRotaGraph(steakX[2], steakY[2], 0.9, 0.0, imgmiddle[2], TRUE);
		DrawRotaGraph(x, y, 0.6, 0.0, image, TRUE);

		DrawString(1115, 0, "Shift�L�[�Ń��Z�b�g", GetColor(255, 255, 255));

		//�f�o�b�O�p
		lstrcpy(StrBuf, "���WX"); // ������"���W �w"��StrBuf�ɃR�s�[	
		_itoa(MouseX, StrBuf2, 10); // MouseX�̒l�𕶎���ɂ���StrBuf2�Ɋi�[
		lstrcat(StrBuf, StrBuf2); // StrBuf�̓��e��StrBuf2�̓��e��t������
		lstrcat(StrBuf, " Y "); // StrBuf�̓��e�ɕ�����"�x"��t������
		_itoa(MouseY, StrBuf2, 10); // MouseY�̒l�𕶎���ɂ���StrBuf2�Ɋi�[
		lstrcat(StrBuf, StrBuf2); // StrBuf�̓��e��StrBuf2�̓��e��t������
		DrawString(0, 0, StrBuf, StringCr);

		ScreenFlip();//����ʂ�\��ʂɔ��f

		DrawBox(0, 0, 200, 32, BoxCr, TRUE);

		//10�b�̉����̂���10�b��1��Đ�
		if (SoundCounter % 600 == 0) {
			PlaySoundMem(Handle, DX_PLAYTYPE_BACK, FALSE); // ���ʉ����Đ�����
		}
		AudioCheck();	//�}�E�X�����̌��ʉ��Đ���ԃ`�F�b�N
		AreaCheck(545, 510, 420, 310, 0, true);		//���̓��𓮂������`�F�b�N
		AreaCheck(800, 750, 420, 310, 2, false);	//�E�̓��𓮂������`�F�b�N
	}

	DxLib_End();
}

