//Initialize Spidar Mouse device
extern "C" _declspec(dllexport) int OpenSpidarMouse();

//set the output force of device, which is defined by the scale of maximum force(from 0 to 1.0). 
//And also the duration of the force, the unit is millisecond.
extern "C" _declspec(dllexport) void SetForce(float Force_XScale,float Force_YScale, int duration);

//stop Spidar Mouse device
extern "C" _declspec(dllexport) bool CloseSpidarMouse();

//set the duty value(0.0-1.0) of string minimum force 
extern "C" _declspec(dllexport) void SetMinForceDuty(float MinForceDuty);

//set output force of device
extern "C" _declspec(dllexport) void SetDutyOnCh(float duty1, float duty2, float duty3, float duty4, int duration);
