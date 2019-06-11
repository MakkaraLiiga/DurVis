#include "SharedMemory.h"

SharedMemory::SharedMemory() {
    using namespace boost::interprocess;
    try {
        windows_shared_memory wsmTimer(open_only, "Durazno2Timer", read_write);
        for (int port = 0; port < 4; port++) {
            mapped_region temp(wsmTimer, read_write, 0, sizeof(times_[0]));
            timesRegion_[port].swap(temp);
        }

        windows_shared_memory wsmCheck(open_only, "Durazno2DurvisCheck", read_write);
        mapped_region temp(wsmCheck, read_write, 0, sizeof(bool));
        durvisCheck_.swap(temp);

        windows_shared_memory wsmStates(open_only, "Durazno2Gamepadstates", read_only);
        for (int port = 0; port < 4; port++) {
            mapped_region temp(wsmStates, read_only, port*SIZE_OF_GAMEPAD_, SIZE_OF_GAMEPAD_);
            befor_[port].swap(temp);
        }
        for (int port = 0; port < 4; port++) {
            mapped_region temp(wsmStates, read_only, (4 + port)*SIZE_OF_GAMEPAD_, SIZE_OF_GAMEPAD_);
            after_[port].swap(temp);
        }

        isMapped_ = true;
    }
    catch (const interprocess_exception& ex) {
        for (int port = 0; port < 4; port++) {
            memset(&beforStates_[port], 0, SIZE_OF_GAMEPAD_);
            memset(&afterStates_[port], 0, SIZE_OF_GAMEPAD_);
        }

        isMapped_ = false;
    }
}

bool SharedMemory::IsMapped() {
    return isMapped_;
}

void SharedMemory::SetServing(bool servePlease) {
    if (isMapped_)
        memcpy(durvisCheck_.get_address(), &servePlease, sizeof(bool));
}

uint8_t SharedMemory::GetDuration(int port) {
    memcpy(&times_[port], timesRegion_[port].get_address(), sizeof(times_[port]));
    return times_[port];
}

XINPUT_STATE SharedMemory::GetGamepadStateBefor(int port) {
    memcpy(&beforStates_[port].Gamepad, befor_[port].get_address(), SIZE_OF_GAMEPAD_);
    return beforStates_[port];
}

XINPUT_STATE SharedMemory::GetGamepadStateAfter(int port) {
    memcpy(&afterStates_[port].Gamepad, after_[port].get_address(), SIZE_OF_GAMEPAD_);
    return afterStates_[port];
}

