#include "DxLib.h"

//共通の変数使用
extern int counter;
extern int steakX[4];
extern int MouseX, MouseY;
extern int Handle1;
extern int AudioCounter;
extern bool AudioPlay;

void CutAudioStart() {
	if (AudioPlay == false) {
		PlaySoundMem(Handle1, DX_PLAYTYPE_BACK, FALSE);
		AudioPlay = true;
	}
}

void AreaCheck(int xMax, int xMin, int yMax, int yMin, int group, bool goLeft) {
	if ((MouseX > xMin) && (MouseX < xMax)) {
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

	if ((MouseY > yMin) && (MouseY < yMax)) {
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

void AudioCheck() {
	if (AudioPlay == true) {
		AudioCounter++;
		if (AudioCounter % 600 == 0) {
			AudioPlay = false;
			AudioCounter = 0;
		}
	}
}

void ResetArea() {
	counter = 0;
	steakX[0] = 180;
	steakX[1] = 304;
	steakX[2] = 428;
	AudioCounter = 0;
	AudioPlay = false;
}
