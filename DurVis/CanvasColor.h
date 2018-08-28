#pragma once
class CanvasColor
{
private:
	struct RgbaColor
	{
		unsigned char r, g, b, a;
	};

public:
	CanvasColor();
	~CanvasColor();
};

