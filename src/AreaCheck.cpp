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

//肉を切るときの音再生関数
void CutAudioStart() {
	//重複再生防止
	if (AudioPlay == false) {
		//バックグラウンドで再生
		PlaySoundMem(Handle1, DX_PLAYTYPE_BACK, FALSE);
		AudioPlay = true;
	}
}

//肉の画像を動かす関数、閾値の設定、方向設定
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

//重複再生防止フラグを初期状態に戻す関数
void AudioCheck() {
	if (AudioPlay == true) {
		AudioCounter++;
		if (AudioCounter % 340 == 0) {
			AudioPlay = false;
			AudioCounter = 0;
		}
	}
}
