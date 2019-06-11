#pragma once
#include "bakkesmod/wrappers/canvaswrapper.h"
#include "RgbaColor.h"
#include "IterableQueue.hpp"

class GraphDrawer {
public:
    GraphDrawer(RgbaColor color, Vector2 pos, int length);
    void Draw(CanvasWrapper c, int pushee);
private:
    IterableQueue<int> kue_;
    int length_, min_, max_;
    RgbaColor color_;
    Vector2 pos_;
};

