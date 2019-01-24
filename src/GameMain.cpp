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

//�O���[�o���ϐ��̒�`
int counter = 0;
int steakX[3] = { 406, 648, 890 };
int steakY[3] = { 380, 380, 380 };
int SSX[3][2] = { { 406,380 },{ 648,380 },{ 890,380 } };
int AudioCounter = 0;
bool AudioPlay = false;
bool clickStatus = false;
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
	clickStatus = false;
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
		DrawStringToHandle(1120, 0, "S�L�[�ŉ��o�X�L�b�v", GetColor(255, 255, 255), ASFont);
	}
}

void mousethread() {
	while (1) {
		GetMousePoint(&MouseX, &MouseY);
	}
}

void theardCheck() {
	while (1) {
		if (steakX[0] >= 380) {
			AreaCheck(550, 505, 420, 310, 0, true);		//���̓��𓮂������`�F�b�N
			Sleep(5);
		}
		if (steakX[2] <= 915) {
			AreaCheck(805, 745, 420, 310, 2, false);	//�E�̓��𓮂������`�F�b�N
			Sleep(5);
		}

		if (CheckHitKey(KEY_INPUT_R) != 0) { ResetArea(); }
	}
}

void  mouseControl() {
	while (1) {
		bool Status = false;
		if (MouseY <= 340 && MouseY >= 245) {
			SetDutyOnCh(1.0, 1.0, 0.0, 0.0, 400);
			Status = true;
		}

		if (MouseY >= 380 && MouseY <= 500) {
			SetDutyOnCh(0.0, 0.0, 1.0, 1.0, 400);
			Status = true;
		}

		if (Status == true) {
			Sleep(400);
			Status = false;
		}
	}
}

void AppStart() {
	SetMouseDispFlag(TRUE);

	//���ʕύX
	ChangeVolumeSoundMem(255 * 30 / 100, Handle);
	ChangeVolumeSoundMem(255 * 50 / 100, Handle1);

	StartSteak();

	HANDLE Areaload;
	HANDLE mouseload;
	HANDLE mouseControlH;
	DWORD checkmouse;
	DWORD checkid;
	DWORD mouseController;

	/* �X���b�h�̐��� */
	Areaload = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)theardCheck, NULL, 0, &checkid);
	mouseload = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)mousethread, NULL, 0, &checkmouse);
	mouseControlH = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)mouseControl, NULL, 0, &mouseController);

	while (!ProcessMessage() && !ClearDrawScreen()) {
		//�����b�Z�[�W���� ����ʂ��N���A

		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) { 
			SetMinForceDuty(0.2);
			clickStatus = true;
		}

		if (CheckHitKey(KEY_INPUT_M) != 0) {

			if ((MessageBox(NULL, TEXT("�^�C�g����ʂɖ߂�܂���?"),
				TEXT("SteakCut"), MB_YESNO | MB_ICONQUESTION)) == IDYES) {
				StopSoundMem(Handle);
				StopSoundMem(Handle1);
				CloseHandle(Areaload);
				ResetArea();
				SetMinForceDuty(0.0);
				Scene = eScene_Menu;
				Sleep(1 * 200);
				break;
			}

		}

		/*
		
		if (AntiMem() == true && DebugMode == false) {
			MessageBox(NULL, "[ERROR:0003]\n\n�s���ȑ�������o�������ߏI�����܂��B", "MW-Secure AntiCheat", MB_OK | MB_ICONSTOP);
			CloseSpidarMouse();

			exit(2);
		}
		*/

		//�e��摜�̓ǂݍ���
		DrawRotaGraph(360, 300, 1.0, 0.0, table, TRUE);
		DrawRotaGraph(650, 450, 1.0, 0.0, imgBack, TRUE);
		DrawRotaGraph(steakX[0], steakY[0], 0.9, 0.0, imgmiddle[0], TRUE);
		DrawRotaGraph(steakX[1], steakY[1], 0.9, 0.0, imgmiddle[1], TRUE);
		DrawRotaGraph(steakX[2], steakY[2], 0.9, 0.0, imgmiddle[2], TRUE);
		DrawRotaGraph(MouseX, MouseY, 0.6, 0.0, image, TRUE);

		if (steakX[0] >= 404) {
			DrawStringToHandle(480, 210, "�؂��Ă݂悤!", GetColor(255, 255, 0), ASFont);
			DrawTriangleAA(520, 230, 530, 230, 525, 235, GetColor(255, 255, 0), TRUE);
		}

		if (steakX[2] <= 892) {
			DrawStringToHandle(725, 210, "�؂��Ă݂悤!", GetColor(255, 255, 0), ASFont);
			DrawTriangleAA(765, 230, 775, 230, 770, 235, GetColor(255, 255, 0), TRUE);
		}

		DrawStringToHandle(1155, 0, "R�L�[�Ń��Z�b�g", GetColor(255, 255, 255), ASFont);
		DrawStringToHandle(970, 0, "M�L�[�Ń^�C�g���ɖ߂�", GetColor(255, 255, 255), ASFont);
		DrawStringToHandle(0, 0, "���N���b�N���ăX�e�[�L��؂�n�߂悤!", GetColor(255, 255, 0), ASFont);

		if ((steakX[0] < 380) || (steakX[2] > 915)) {
			DrawStringToHandle(0, 40, "����ȏ�؂邱�Ƃ͂ł��܂���BR�L�[�������ă��Z�b�g���ĉ������B", GetColor(255, 255, 0), ASFont);
		}

		//�f�o�b�O�p
		if (DebugMode == true) {
			OutXYData();
			PicArea();
			FPSPrint();
			FlagControl();
		}

		if (SoundCounter % 600 == 0) {
			PlaySoundMem(Handle, DX_PLAYTYPE_BACK, FALSE); // ���ʉ����Đ�����
		}
		AudioCheck();	//�}�E�X�����̌��ʉ��Đ���ԃ`�F�b�N
		ScreenFlip();//����ʂ�\��ʂɔ��f

	}
}
