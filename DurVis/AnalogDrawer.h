#pragma once
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "RgbaColor.h"

class AnalogDrawer {
public:
    int left = 0;
    int right = 0;
    int top = 0;
    int bottom = 0;
    int margin = 0;

    AnalogDrawer(Vector2 pos, int width, int height, int margin);
    void DrawStickFrame(CanvasWrapper c, RgbaColor color);
    void DrawThrottle(CanvasWrapper c, RgbaColor color, Vector2 pos, int value);
    void DrawThrottle(CanvasWrapper c, RgbaColor color, Vector2 pos, float value);
    void DrawSingleAxis(CanvasWrapper c, RgbaColor color, bool horizontal, float value);
    void DrawDualAxis(CanvasWrapper c, RgbaColor color, int x, int y);
    Vector2 GetPos();
private:
    Vector2 originPos_;
    void DrawNormThrottle(CanvasWrapper c, RgbaColor color, Vector2 pos, float value);
    float StickToNorm(int value);
    float TriggerToNorm(int value);
    const float CANVAS_SCALE_ = 100.0f;
};

