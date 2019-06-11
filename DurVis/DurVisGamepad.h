#pragma once
#include <string>
#include "windows.h"
#include "Xinput.h"

enum Analog {
    LT = 0,
    RT,
    LX,
    LY,
    RX,
    RY,
};

struct GamepadButton {
    int number;
    std::string drawName;
    GamepadButton() {
        number = 0;
        drawName = "";
    }
    GamepadButton(int num, std::string dn) {
        number = num;
        drawName = dn;
    }
};

class DurVisGamepad {
public:
    DurVisGamepad();
    void Update(XINPUT_STATE state);
    uint8_t GetTrigger(int analogControl);
    int16_t GetStick(int analogControl);
    std::string GetButtonsPressedString(std::string delimiter);
    int GetButtonPressedFrames();
private:
    XINPUT_STATE state_;
    GamepadButton buttons[14];

    bool GetButtonPressed(int button);
    int ButtonsPressedFrames_ = 0;
    int ButtonsPressedFramesLast_ = 0;
};
