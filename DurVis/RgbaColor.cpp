#include "RgbaColor.h"

RgbaColor::RgbaColor() {
    r = 255U; g = 255U; b = 255U; a = 255U;
}

RgbaColor::RgbaColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
    r = red; g = green; b = blue; a = alpha;
}
void RgbaColor::Set(CanvasWrapper c) {
    c.SetColor(r, g, b, a);
}
void RgbaColor::Set(CanvasWrapper c, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
    c.SetColor(red, green, blue, alpha);
}
void RgbaColor::Set(CanvasWrapper c, uint8_t alpha) {
    c.SetColor(r, g, b, alpha);
}
