#pragma once
#include <boost/interprocess/windows_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include "windows.h"
#include "Xinput.h"

// accessing shared memory created by Durazno^2
class SharedMemory {
public:
    bool IsMapped();

    SharedMemory();

    // tells Durazno^2 if we want to be served data
    void SetServing(bool servePlease);

    uint8_t GetDuration(int port);
    XINPUT_STATE GetGamepadStateBefor(int port);
    XINPUT_STATE GetGamepadStateAfter(int port);

private:
    bool isMapped_ = false;
    boost::interprocess::mapped_region timesRegion_[4], durvisCheck_, befor_[4], after_[4];
    uint8_t times_[4];
    XINPUT_STATE beforStates_[4], afterStates_[4];
    size_t SIZE_OF_GAMEPAD_ = 12U;
};
