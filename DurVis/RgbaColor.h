#pragma once
#include "bakkesmod/wrappers/canvaswrapper.h"

class RgbaColor {
public:
    uint8_t r, g, b, a;
    RgbaColor();
    RgbaColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
    void Set(CanvasWrapper c);
    void Set(CanvasWrapper c, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void Set(CanvasWrapper c, uint8_t a);
    void SetAlpha(uint8_t alpha);
private:
};

