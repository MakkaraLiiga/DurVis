#include "MappedMemory.h"
#include "bakkesmod/plugin/bakkesmodplugin.h"
//#include "windows.h"
//#include "Xinput.h"

#include <boost/interprocess/windows_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>
//#include <boost/interprocess/shared_memory_object.hpp>

MappedMemory *MappedMemory::instance = 0;

MappedMemory::MappedMemory()
{
	try {
		windows_shared_memory wsm(open_only, "Durazno2SharedMemory", read_only);
		for (int i = 0; i < 4; i++)
		{
			mapped_region temp(wsm, read_only, i*_SIZE_OF_GAMEPAD, _SIZE_OF_GAMEPAD);
			_Befor[i].swap(temp);
		}
		for (int i = 0; i < 4; i++)
		{
			mapped_region temp(wsm, read_only, (4 + i)*_SIZE_OF_GAMEPAD, _SIZE_OF_GAMEPAD);
			_After[i].swap(temp);
		}
		_isMapped = true;
	}
	catch (const interprocess_exception& ex)
	{
		for (int i = 0; i < 4; i++)
		{
			memset(&_BeforStates[i], 0, _SIZE_OF_GAMEPAD);
			memset(&_AfterStates[i], 0, _SIZE_OF_GAMEPAD);
		}
		_isMapped = false;
		//boostMemError = ex.what();
		//logger("./bakkesmod/plugins/inputviewer.log", ex.what());
		//logger("./bakkesmod/plugins/inputviewer.log", "shared memory not found");
	}
}

bool MappedMemory::isMapped()
{
	return _isMapped;
}

_XINPUT_STATE MappedMemory::getGamepadStateBefor(int i)
{
	memcpy(&_BeforStates[i].Gamepad, _Befor[i].get_address(), _SIZE_OF_GAMEPAD);
	return _BeforStates[i];
}

_XINPUT_STATE MappedMemory::getGamepadStateAfter(int i)
{
	memcpy(&_AfterStates[i].Gamepad, _After[i].get_address(), _SIZE_OF_GAMEPAD);
	return _AfterStates[i];
}

MappedMemory::~MappedMemory()
{
}

