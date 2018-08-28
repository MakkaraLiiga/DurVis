#pragma once
#pragma comment( lib, "bakkesmod.lib" )
#include "bakkesmod/plugin/bakkesmodplugin.h"

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


struct frame {
	float timestamp = .0;
	ControllerInput input = { 0 };
	Vector locationData = { 0 };
	Rotator rotationData = { 0 };
	Vector velocityData = { 0 };
};

class DurVisPlugin : public BakkesMod::Plugin::BakkesModPlugin
{
private:
	std::shared_ptr<bool> enabled;
public:
	virtual void onLoad();
	virtual void onUnload();
	//void logger(string filename, string string);
	/*void OnMacroCommand(std::vector<std::string> params);
	void OnBeforAsync(std::string funcName);
	void OnAfterAsync(std::string funcName);
	void OnRecordTick();
	void OnPlaybackTick();*/
	static frame interp(std::shared_ptr<frame> f1, std::shared_ptr<frame> f2, float elaps);
	void Render(CanvasWrapper canvas);

};
