#include "AnalogDrawer.h"

AnalogDrawer::AnalogDrawer(Vector2 pos, int width, int height, int m) {
    originPos_ = pos;
    left = pos.X;
    top = pos.Y;
    right = width;
    bottom = height;
    margin = m;
}

void AnalogDrawer::DrawStickFrame(CanvasWrapper c, RgbaColor color) {
    color.Set(c, 150);

    int hw = right / 2;
    int hh = bottom / 2;
    int hm = 10 / 2;

    // cross
    c.DrawLine(originPos_.minus({ hw, -hm }), originPos_.minus({ -(hw+margin), -hm }));
    c.DrawLine(originPos_.minus({ hm, -hh }), originPos_.minus({ -hm, -(hh-margin) }));

    c.SetPosition(originPos_.minus({ hw, hh }));
    c.DrawBox({ right + margin, bottom + margin });
    // background
    color.Set(c, 100);
    c.FillBox({ right + margin, bottom + margin });
}

void AnalogDrawer::DrawThrottle(CanvasWrapper c, RgbaColor color, Vector2 pos, int value) {
    DrawNormThrottle(c, color, pos, TriggerToNorm(value));
}

void AnalogDrawer::DrawThrottle(CanvasWrapper c, RgbaColor color, Vector2 pos, float value) {
    DrawNormThrottle(c, color, pos, value);
}

void AnalogDrawer::DrawNormThrottle(CanvasWrapper c, RgbaColor color, Vector2 pos, float value) {
    value = abs(CANVAS_SCALE_ * value);
    color.Set(c);
    pos = pos.minus({ -originPos_.X, -originPos_.Y });
    c.DrawRect(pos, pos.minus({ -static_cast<int>(value), -10 }));
}

float AnalogDrawer::StickToNorm(int value) {
    return value / 32768.0f;
}

float AnalogDrawer::TriggerToNorm(int value) {
    return value / 255.0f;
}

void AnalogDrawer::DrawSingleAxis(CanvasWrapper c, RgbaColor color, bool horizontal, float value) {
    color.Set(c);

    Vector2 pos = originPos_;

    int valueInt = static_cast<int>(CANVAS_SCALE_ * value) + 5;
    if (horizontal)
        c.DrawLine(pos.minus({ -valueInt, 100 }), pos.minus({ -valueInt, -110 }));
    else
        c.DrawLine(pos.minus({ 100, -valueInt }), pos.minus({ -110, -valueInt }));
}

void AnalogDrawer::DrawDualAxis(CanvasWrapper c, RgbaColor color, int x, int y) {
    color.Set(c);

    x = static_cast<int>(CANVAS_SCALE_ * StickToNorm(x));
    y = -static_cast<int>(CANVAS_SCALE_ * StickToNorm(y));

    Vector2 pos = originPos_;
    pos = pos.minus({ -x, -y });
    c.SetPosition(pos);
    c.DrawBox({ 10, 10 });
}

Vector2 AnalogDrawer::GetPos() {
    return originPos_;
}