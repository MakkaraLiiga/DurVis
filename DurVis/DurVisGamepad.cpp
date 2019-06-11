#include "DurVisGamepad.h"
#include "SharedMemory.h"

DurVisGamepad::DurVisGamepad() {
    buttons[0] = GamepadButton(XINPUT_GAMEPAD_DPAD_UP, "Dup");
    buttons[1] = GamepadButton(XINPUT_GAMEPAD_DPAD_DOWN, "Ddown");
    buttons[2] = GamepadButton(XINPUT_GAMEPAD_DPAD_LEFT, "Dleft");
    buttons[3] = GamepadButton(XINPUT_GAMEPAD_DPAD_RIGHT, "Dright");
    buttons[4] = GamepadButton(XINPUT_GAMEPAD_START, "Start");
    buttons[5] = GamepadButton(XINPUT_GAMEPAD_BACK, "Back");
    buttons[6] = GamepadButton(XINPUT_GAMEPAD_LEFT_THUMB, "LS");
    buttons[7] = GamepadButton(XINPUT_GAMEPAD_RIGHT_THUMB, "RS");
    buttons[8] = GamepadButton(XINPUT_GAMEPAD_LEFT_SHOULDER, "LB");
    buttons[9] = GamepadButton(XINPUT_GAMEPAD_RIGHT_SHOULDER, "RB");
    buttons[10] = GamepadButton(XINPUT_GAMEPAD_A, "A");
    buttons[11] = GamepadButton(XINPUT_GAMEPAD_B, "B");
    buttons[12] = GamepadButton(XINPUT_GAMEPAD_X, "X");
    buttons[13] = GamepadButton(XINPUT_GAMEPAD_Y, "Y");
}

void DurVisGamepad::Update(XINPUT_STATE state) {
    state_ = state;
}

uint8_t DurVisGamepad::GetTrigger(int analogControl) {
    switch (analogControl) {
        case Analog::LT: return state_.Gamepad.bLeftTrigger;
        case Analog::RT: return state_.Gamepad.bRightTrigger;
        default: return 0;
    }
}

int16_t DurVisGamepad::GetStick(int analogControl) {
    switch (analogControl) {
        case Analog::LX: return state_.Gamepad.sThumbLX;
        case Analog::LY: return state_.Gamepad.sThumbLY;
        case Analog::RX: return state_.Gamepad.sThumbRX;
        case Analog::RY: return state_.Gamepad.sThumbRY;
        default: return 0;
    }
}

std::string DurVisGamepad::GetButtonsPressedString(std::string delimiter) {
    std::string r = "";
    for (int i = 0; i < 14; i++) {
        if (GetButtonPressed(i)) {
            if (r != "") r += delimiter;
            r += buttons[i].drawName;
        }
    }
    if (r == "") {
        ButtonsPressedFrames_ = 0;
    } else {
        ButtonsPressedFrames_++;
        ButtonsPressedFramesLast_ = ButtonsPressedFrames_;
    }
    return std::to_string(ButtonsPressedFramesLast_) + "f " + r;
}

int DurVisGamepad::GetButtonPressedFrames() {
    return ButtonsPressedFramesLast_;
}

bool DurVisGamepad::GetButtonPressed(int buttonIndex) {
    return ( state_.Gamepad.wButtons & buttons[buttonIndex].number ) != 0;
}