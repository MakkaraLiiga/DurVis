#pragma once
#include <string>
#include "bakkesmod/wrappers/canvaswrapper.h"
#include "RgbaColor.h"

class TextDrawer {
public:
    TextDrawer(Vector2 pos, RgbaColor colorBg, int columnWidth, int lineHeight);
    void SetLine(int line);
    void SetPos(Vector2 pos);
    void WriteLine();
    void WriteLine(CanvasWrapper c, string text);
    void WriteLine(CanvasWrapper c, RgbaColor color, string text);
    void WriteLine(CanvasWrapper c, RgbaColor color, string name, string value);
    void WriteLine(CanvasWrapper c, RgbaColor color, string name, string value1, string value2);
    void WriteStick(CanvasWrapper c, RgbaColor color, string name, int16_t value);
    void WriteTrigger(CanvasWrapper c, RgbaColor color, string name, uint8_t value);

    Vector2 GetPos();
    int GetMaxHeight();
    void Reset();

private:
    Vector2 pos_, originPos_;
    int lineHeight_;
    int columnWidth_;
    int currentLine_;
    int maxHeight_;
    RgbaColor colorBg_;
};

