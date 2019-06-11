#include "GraphDrawer.h"

GraphDrawer::GraphDrawer(RgbaColor color, Vector2 pos, int length) {
    color_ = color;
    pos_ = pos;
    length_ = length;
    for (int i = 0; i < length_; i++) {
        kue_.push(0);
    }
}

void GraphDrawer::Draw(CanvasWrapper c, int pushee) {
    color_.Set(c);
    Vector2 pos = pos_;

    c.SetPosition(pos);
    c.DrawString("XInputGetState execution");
    pos = pos.minus({ 0, -12 });
    c.SetPosition(pos);
    c.DrawString("duration in microseconds:");
    pos = pos.minus({ 0, -12 });
    c.SetPosition(pos);
    c.DrawString("Min " + to_string(min_) + " Max " + to_string(max_));
    pos = pos.minus({ 0, -24 });

    kue_.push(pushee);
    if (kue_.size() > length_) kue_.pop();
    int i = 0;
    max_ = 0;
    min_ = INT16_MAX;
    for (auto it = kue_.begin(); it != kue_.end(); ++it) {
        int intIt = static_cast<int>(*it);
        c.DrawLine(pos.minus({ 0, -(length_ - i) }), pos.minus({ -intIt, -(length_ - i) }));
        min_ = std::min(min_, intIt);
        max_ = std::max(max_, intIt);
        i++;
    }
}