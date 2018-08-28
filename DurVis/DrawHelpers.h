#pragma once
#pragma comment( lib, "bakkesmod.lib" )
#include "bakkesmod/plugin/bakkesmodplugin.h"

class ColorHelper
{
private:
	struct RgbaColor
	{
		unsigned char r, g, b, a;
	};
	RgbaColor colorXInput = { 200, 0, 0, 200 };
	RgbaColor colorDurazno = { 0, 0, 200, 200 };
	RgbaColor colorCi = { 0, 200, 0, 200 };
	RgbaColor colorText = { 200, 0, 200, 200 };
	RgbaColor colorBefor = { 200,0,0,250 };
	RgbaColor colorAfter = { 0,0,200,250 };
public:
	ColorHelper();
	void getColor(CanvasWrapper c, RgbaColor rgba)
	{
		c.SetColor(rgba.r, rgba.g, rgba.b, rgba.a);
	}
};
