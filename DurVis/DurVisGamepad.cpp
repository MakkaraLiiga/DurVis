#include "DurVisGamepad.h"
#include "MappedMemory.h"
#include "bakkesmod/plugin/bakkesmodplugin.h"

DurVisGamepad::DurVisGamepad(int source)
{
	_source = source;
}

void DurVisGamepad::update(int i)
{
	DWORD dwResult;
	//get state from mem region
	if (_source == 0) _state = MappedMemory::getInstance()->getGamepadStateBefor(i);
	else if (_source == 1) _state = MappedMemory::getInstance()->getGamepadStateAfter(i);
	//else if (_source == 2) dwResult = XInputGetState(i, &_state);
}

int DurVisGamepad::getAnalog(int analogControl)
{
	switch (analogControl)
	{
		case Gamepad::LT: return _state.Gamepad.bLeftTrigger;
		case Gamepad::RT: return _state.Gamepad.bRightTrigger;
		case Gamepad::LX: return _state.Gamepad.sThumbLX;
		case Gamepad::LY: return _state.Gamepad.sThumbLY;
		case Gamepad::RX: return _state.Gamepad.sThumbRX;
		case Gamepad::RY: return _state.Gamepad.sThumbRY;
		default: return 0;
	}
}

string DurVisGamepad::getButtonsPressedString(string delimiter)
{
	string r = "";
	for (int i = 0; i < 14; i++)
	{
		if (getButtonPressed(i))
		{
			if (r != "") r += delimiter;
			r += getButtonAsString(i);
		}
	}
	return r;
}

bool DurVisGamepad::getButtonPressed(int button)
{
	return (_state.Gamepad.wButtons & getButtonStateByNumber(button)) != 0;
}

int DurVisGamepad::getButtonStateByNumber(int num)
{
	switch (num)
	{
	case 0:		return XINPUT_GAMEPAD_DPAD_UP;
	case 1:		return XINPUT_GAMEPAD_DPAD_DOWN;
	case 2:		return XINPUT_GAMEPAD_DPAD_LEFT;
	case 3:		return XINPUT_GAMEPAD_DPAD_RIGHT;
	case 4:		return XINPUT_GAMEPAD_START;
	case 5:		return XINPUT_GAMEPAD_BACK;
	case 6:		return XINPUT_GAMEPAD_LEFT_THUMB;
	case 7:		return XINPUT_GAMEPAD_RIGHT_THUMB;
	case 8:		return XINPUT_GAMEPAD_LEFT_SHOULDER;
	case 9:		return XINPUT_GAMEPAD_RIGHT_SHOULDER;
	case 10:	return XINPUT_GAMEPAD_A;
	case 11:	return XINPUT_GAMEPAD_B;
	case 12:	return XINPUT_GAMEPAD_X;
	case 13:	return XINPUT_GAMEPAD_Y;
	default: return 0;
	}
}

string DurVisGamepad::getButtonAsString(int num)
{
	switch (num)
	{
	case 0:		return "Dup";
	case 1:		return "Ddown";
	case 2:		return "Dleft";
	case 3:		return "Dright";
	case 4:		return "Start";
	case 5:		return "Back";
	case 6:		return "LS";
	case 7:		return "RS";
	case 8:		return "LB";
	case 9:		return "RB";
	case 10:	return "A";
	case 11:	return "B";
	case 12:	return "X";
	case 13:	return "Y";
	default: return "";
	}
}

DurVisGamepad::~DurVisGamepad()
{
}
