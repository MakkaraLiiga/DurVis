#pragma once
#pragma comment( lib, "bakkesmod.lib" )

#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "windows.h"
#include "Xinput.h"

#include <boost/interprocess/windows_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>
//#include <boost/interprocess/shared_memory_object.hpp>

using namespace boost::interprocess;

//singleton
class MappedMemory
{
private:
	static MappedMemory *instance;
	MappedMemory();
	bool _isMapped = false;

	mapped_region _Befor[4];
	mapped_region _After[4];

	_XINPUT_STATE _BeforStates[4];
	_XINPUT_STATE _AfterStates[4];

	size_t _SIZE_OF_GAMEPAD = 12U;

public:
	static MappedMemory *getInstance()
	{
		if (!instance)
			instance = new MappedMemory;
		return instance;
	}
	bool isMapped();
	_XINPUT_STATE getGamepadStateBefor(int i);
	_XINPUT_STATE getGamepadStateAfter(int i);
	~MappedMemory();
};