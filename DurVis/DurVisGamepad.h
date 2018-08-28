#pragma once
#pragma comment( lib, "bakkesmod.lib" )
#pragma comment( lib, "XInput.lib" )
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "windows.h"
#include "Xinput.h"
//#include "MappedMemory.h"

enum Gamepad
{
	LT = 0,
	RT,
	LX,
	LY,
	RX,
	RY,
};

enum source
{
	DuraznoBefor,
	DuraznoAfter,
	VanillaXinput
};

class DurVisGamepad
{
public:
	DurVisGamepad(int source);
	void update(int i);
	int getAnalog(int control);
	string getButtonsPressedString(string delimiter);
	bool getButtonPressed(int button);
	int getButtonStateByNumber(int num);
	string getButtonAsString(int num);
	~DurVisGamepad();
private:
	int _source;
	_XINPUT_STATE _state;
	//MappedMemory _mm;
};

