#include "CanvasWriter.h"
#include "bakkesmod/plugin/bakkesmodplugin.h"

CanvasWriter::CanvasWriter(Vector2 pos, int lineHeight)
{
	_lineHeight = lineHeight;
	_pos = _startPos = pos;
	_currentLine = 0;
}

void CanvasWriter::reset()
{
	_pos = _startPos;
	_currentLine = 0;
}

void CanvasWriter::setLine(int line)
{
	_currentLine = line;
}

void CanvasWriter::setPos(Vector2 pos)
{
	_pos = pos;
}

void CanvasWriter::writeLine()
{
	_pos = _pos.plus({ 0, _lineHeight });
}

void CanvasWriter::writeLine(CanvasWrapper c, string name, int value)
{
	writeLine(c, name, to_string(value));
}

void CanvasWriter::writeLine(CanvasWrapper c, string name, unsigned long value)
{
	writeLine(c, name, to_string(value));
}

void CanvasWriter::writeLine(CanvasWrapper c, string name, float value)
{
	writeLine(c, name, to_string(value));
}

void CanvasWriter::writeLine(CanvasWrapper c, string name, string value)
{
	c.SetPosition(_pos);
	c.DrawString(name);
	c.SetPosition(_pos.plus({ 100, 0 }));
	c.DrawString(value);
	_pos = _pos.plus({ 0, _lineHeight });
}


CanvasWriter::~CanvasWriter()
{
}
