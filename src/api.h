#pragma once

int ConnectDevice();
int DisconnectDevice();
void ConnectStatus();
void OutPower(float x, float y, int msec);
void SetMinPower(float MinDuty);
void OutPowerAll(float Ch1Duty, float Ch2Duty, float Ch3Duty, float Ch4Duty, int mset);