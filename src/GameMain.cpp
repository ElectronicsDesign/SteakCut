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

//�O���[�o���ϐ��̒�`
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

	//���ʕύX
	ChangeVolumeSoundMem(255 * 30 / 100, Handle);
	ChangeVolumeSoundMem(255 * 50 / 100, Handle1);


	while (!ProcessMessage() && !ClearDrawScreen() && !GetHitKeyStateAll(Key) && !Key[KEY_INPUT_ESCAPE]) {
		//�����b�Z�[�W���� ����ʂ��N���A ���L�[�{�[�h���͏�Ԏ擾 ��ESC��������Ă��Ȃ�

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
			MessageBox(NULL, "�s���ȑ�������o�������ߏI�����܂��B[ERROR:0003 �������̉����񌟒m]", "MW-Secure AntiCheat", MB_OK);
			exit(2);
		}

		//�e��摜�̓ǂݍ���
		DrawRotaGraph(650, 450, 1.0, 0.0, imgBack, TRUE);
		DrawRotaGraph(steakX[0], steakY[0], 0.9, 0.0, imgmiddle[0], TRUE);
		DrawRotaGraph(steakX[1], steakY[1], 0.9, 0.0, imgmiddle[1], TRUE);
		DrawRotaGraph(steakX[2], steakY[2], 0.9, 0.0, imgmiddle[2], TRUE);
		DrawRotaGraph(MouseX, MouseY, 0.6, 0.0, image, TRUE);

		DrawStringToHandle(1155, 0, "R�L�[�Ń��Z�b�g", GetColor(255, 255, 255), ASFont);
		DrawStringToHandle(970, 0, "M�L�[�Ń^�C�g���ɖ߂�", GetColor(255, 255, 255), ASFont);

		if ((steakX[0] <= 380) || (steakX[2] >= 915)) {
			DrawStringToHandle(0, 0, "����ȏ�؂邱�Ƃ͂ł��܂���BR�L�[�������ă��Z�b�g���ĉ������B", GetColor(255, 255, 0), ASFont);
		}
		else {
			AreaCheck(550, 505, 420, 310, 0, true);		//���̓��𓮂������`�F�b�N
			AreaCheck(805, 745, 420, 310, 2, false);	//�E�̓��𓮂������`�F�b�N
		}

		//�f�o�b�O�p
		OutXYData();
		FPSPrint();

		ScreenFlip();//����ʂ�\��ʂɔ��f

		//10�b�̉����̂���10�b��1��Đ�
		if (SoundCounter % 600 == 0) {
			PlaySoundMem(Handle, DX_PLAYTYPE_BACK, FALSE); // ���ʉ����Đ�����
		}
		AudioCheck();	//�}�E�X�����̌��ʉ��Đ���ԃ`�F�b�N


	}
}