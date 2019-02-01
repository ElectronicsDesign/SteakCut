#define _CRT_SECURE_NO_WARNINGS
#include "DxLib.h"
#include "MenuArea.h"

bool DebugMode = false;

//�N�����Ɏ��s(main�֐�)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	SetGraphMode(1280, 800, 32);	//�`��ݒ��1280 x 800, 32bit�J���[�ɐݒ�
	SetWindowSize(1280, 800);	//�E�B���h�E�T�C�Y��1280 x 800�ɐݒ�
	SetMainWindowText("SteakCut");	//�A�v���P�[�V�����^�C�g����SteakCut�ɐݒ�
	SetWindowIconID(101);

	if (ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK || DxLib_Init() == -1) return -1;

	if ((LoadGraphScreen(240, 220, "./img/Devlogo.png", TRUE)) == -1) {
		MessageBox(NULL, "[ERROR : 0000]\n\n�t�@�C�����s�����ł��B�ă_�E�����[�h���Ă��������B", "EteakCut Start Error", MB_OK | MB_ICONERROR);
		exit(9);
	}
	DrawString(450, 480, "�N���� :", GetColor(255, 255, 255));
	DrawBoxAA(550, 480, 720, 495, GetColor(255, 255, 255), FALSE);
	LoadGraphScreen(460, 620, "./img/shift.png", TRUE);
	DrawString(550, 632, "Press Shift to Debug Mode", GetColor(255, 255, 255));

	LoadMem();	//�摜�A�������������ɓW�J�J�n
	MenuOn();	//�^�C�g����ʂ֑J��

	return 0;
}
