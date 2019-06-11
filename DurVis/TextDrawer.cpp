#include "TextDrawer.h"

TextDrawer::TextDrawer(Vector2 pos, RgbaColor colorBg, int columnWidth, int lineHeight) {
    colorBg_ = colorBg;
    columnWidth_ = columnWidth;
    lineHeight_ = lineHeight;
    pos_ = originPos_ = pos;
    currentLine_ = 0;
}

void TextDrawer::Reset() {
    pos_ = originPos_;
    maxHeight_ = currentLine_ * lineHeight_;
    currentLine_ = 0;
}

int TextDrawer::GetMaxHeight() {
    return maxHeight_;
}

void TextDrawer::SetLine(int line) {
    currentLine_ = line;
}

void TextDrawer::SetPos(Vector2 pos) {
    pos_ = pos;
}

void TextDrawer::WriteLine() {
    pos_ = pos_.minus({ 0, -lineHeight_ });
}

void TextDrawer::WriteLine(CanvasWrapper c, string text) {
    c.SetPosition(pos_);
    c.DrawString(text);
    pos_ = pos_.minus({ 0, -lineHeight_ });
    currentLine_++;
}

void TextDrawer::WriteStick(CanvasWrapper c, RgbaColor color, string name, int16_t value) {
    WriteLine(c, color, name, to_string(value/32768.0f), to_string(value));
}

void TextDrawer::WriteTrigger(CanvasWrapper c, RgbaColor color, string name, uint8_t value) {
    WriteLine(c, color, name, to_string(value/255.0f), to_string(value));
}

void TextDrawer::WriteLine(CanvasWrapper c, RgbaColor color, string name, string value) {
    WriteLine(c, color, name, value, "");
}

void TextDrawer::WriteLine(CanvasWrapper c, RgbaColor color, string string) {
    WriteLine(c, color, string, "", "");
}

void TextDrawer::WriteLine(CanvasWrapper c, RgbaColor color, string name, string value1, string value2) {
    color.Set(c);
    c.SetPosition(pos_);
    c.DrawString(name);
    if (value2 != "") {
        c.SetPosition(pos_.minus({ -2 * columnWidth_, 0 }));
        c.DrawString(value2);
    }
    if (value1 != "") {
        c.SetPosition(pos_.minus({ -columnWidth_, 0 }));
        c.DrawString(value1);
    }
    pos_ = pos_.minus({ 0, -lineHeight_ });
    currentLine_++;
}

Vector2 TextDrawer::GetPos() {
    return originPos_;
}