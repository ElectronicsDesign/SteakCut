#include "DxLib.h"
#include "SpidarMouse.h"

int sleepTimer = 30;
int mortorTimer = 100;
float PlusXPower = 5.0;
float MinusXPower = -5.0;
float PlusYPower = 0.0;
float MinusYPower = 0.0;

extern int counter;
extern int steakX[3];
extern int MouseX, MouseY;
extern int Handle1;
extern int AudioCounter;
extern bool AudioPlay;
extern bool clickStatus;

//����؂�Ƃ��̉��Đ��֐�
void CutAudioStart() {
	//�d���Đ��h�~
	if (AudioPlay == false) {
		//�o�b�N�O���E���h�ōĐ�
		PlaySoundMem(Handle1, DX_PLAYTYPE_BACK, FALSE);
		AudioPlay = true;
	}
}

//���̉摜�𓮂����֐��A臒l�̐ݒ�A�����ݒ�
void AreaCheck(int xMax, int xMin, int yMax, int yMin, int group, bool goLeft) {
	if ((MouseX > xMin) && (MouseX < xMax) && clickStatus == true) {
		if ((MouseY > yMin) && (MouseY < yMax)) {
			counter++;
			if (counter == 30) {
				if (goLeft == true) {
					steakX[group]--;
				}
				else {
					steakX[group]++;
				}
				counter = 0;
				CutAudioStart();
			}
		}
	}

	if ((MouseY > yMin) && (MouseY < yMax) && clickStatus == true) {
		if ((MouseX > xMin) && (MouseX < xMax)) {
			counter++;
			if (counter == 30) {
				if (goLeft == true) {
					steakX[group]--;
				}
				else {
					steakX[group]++;
				}
				counter = 0;
				CutAudioStart();
			}
		}
	}
}

//�d���Đ��h�~�t���O��������Ԃɖ߂��֐�
void AudioCheck() {
	if (AudioPlay == true) {
		AudioCounter++;
		if (AudioCounter % 340 == 0) {
			AudioPlay = false;
			AudioCounter = 0;
		}
	}
}
