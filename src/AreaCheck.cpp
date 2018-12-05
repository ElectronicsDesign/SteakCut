#include "DxLib.h"

extern int counter;
extern int steakX[4];
extern int steakY[4];
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

void AreaCheckA() {
	if ((MouseX > 200) && (MouseX < 270)) {
		if ((MouseY > 180) && (MouseY < 200)) {
			counter++;
			if (counter == 30) {
				steakX[0]--;
				counter = 0;
				CutAudioStart();
			}
		}
	}

	if ((MouseY > 180) && (MouseY < 220)) {
		if ((MouseX > 200) && (MouseX < 270)) {
			counter++;
			if (counter == 30) {
				steakX[0]--;
				counter = 0;
				CutAudioStart();
			}
		}
	}
}

void AreaCheckB() {
	if ((MouseX > 350) && (MouseX < 516)) {
		if ((MouseY > 150) && (MouseY < 200)) {
			counter++;
			if (counter == 30) {
				steakX[2]++;
				counter = 0;
				CutAudioStart();
			}
		}
	}

	if ((MouseY > 150) && (MouseY < 220)) {
		if ((MouseX > 350) && (MouseX < 496)) {
			counter++;
			if (counter == 30) {
				steakX[2]++;
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