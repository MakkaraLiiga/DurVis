#pragma once
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "DrawHelpers.h"

class CanvasWriter
{
public:
	CanvasWriter(Vector2 pos, int lineHeight);
	void setLine(int line);
	void setPos(Vector2 pos);
	void writeLine();
	void writeLine(CanvasWrapper c, string name, int value);
	void writeLine(CanvasWrapper c, string name, unsigned long value);
	void writeLine(CanvasWrapper c, string name, float value);
	void writeLine(CanvasWrapper c, string name, string value);
	void reset();
	~CanvasWriter();
private:
	Vector2 _pos, _startPos;
	int _lineHeight;
	int _currentLine;
};

