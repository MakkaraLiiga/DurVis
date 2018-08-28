#include "DurVis.h"
#include "CanvasWriter.h"
#include "DurVisGamepad.h"
#include "bakkesmod/wrappers/GameEvent/ServerWrapper.h"
#include "bakkesmod/wrappers/GameObject/CarWrapper.h"
#include "bakkesmod/wrappers/ArrayWrapper.h"
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "MappedMemory.h"

BAKKESMOD_PLUGIN(DurVisPlugin, "DurVis plugin", "0.1", PLUGINTYPE_FREEPLAY | PLUGINTYPE_CUSTOM_TRAINING)

CanvasWriter w = CanvasWriter({ 10, 160 }, 12);
DurVisGamepad gamepadBefor(source::DuraznoBefor);
DurVisGamepad gamepadAfter(source::DuraznoAfter);
//DurVisGamepad gamepadVanil(source::VanillaXinput);


void CanvasSetColor(CanvasWrapper c, RgbaColor rgba)
{
	c.SetColor(rgba.r, rgba.g, rgba.b, rgba.a);
}


void DurVisPlugin::onLoad()
{
	enabled = make_shared<bool>(true);
	cvarManager->registerCvar("durvis_enabled", "1", "Enable DurVis", true, true, 0, true, 1).bindTo(enabled);
	cvarManager->registerCvar("durvis_xinput_port", "0", "XInput port", true, true, 0, true, 3);
	gameWrapper->RegisterDrawable(std::bind(&DurVisPlugin::Render, this, std::placeholders::_1));
}

void DurVisPlugin::onUnload()
{
	//enabled = false;
}

void DurVisPlugin::Render(CanvasWrapper c)
{
	if (*enabled && gameWrapper->IsInGame())
	{

		ServerWrapper server = gameWrapper->GetGameEventAsServer();
		auto players = gameWrapper->GetGameEventAsServer().GetCars();
		CarWrapper player0 = players.Get(0);
		ControllerInput ci = player0.GetInput();
		std::shared_ptr<frame> fr(new frame());
		fr->timestamp = server.GetSecondsElapsed();
		fr->input = ci;
		fr->locationData = player0.GetLocation();
		fr->rotationData = player0.GetRotation();
		fr->velocityData = player0.GetVelocity();

		CanvasSetColor(c, colorText);

		w.writeLine(c, "Throttle", ci.Throttle);
		w.writeLine(c, "Steer", ci.Steer);
		w.writeLine(c, "Yaw", ci.Yaw);
		w.writeLine(c, "Pitch", ci.Pitch);
		w.writeLine(c, "Roll", ci.Roll);
		w.writeLine(c, "DodgeForward", ci.DodgeForward);
		w.writeLine(c, "DodgeStrafe", ci.DodgeStrafe);
		w.writeLine(c, "Jump", ci.Jump);
		w.writeLine(c, "Jumped", ci.Jumped);
		w.writeLine(c, "ActivateBoost", ci.ActivateBoost);
		w.writeLine(c, "HoldingBoost", ci.HoldingBoost);
		w.writeLine(c, "Handbrake", ci.Handbrake);

		if (MappedMemory::getInstance()->isMapped())
		{
			gamepadBefor.update(0);
			gamepadAfter.update(0);
			w.writeLine();
			w.writeLine(c, "Buttons", gamepadBefor.getButtonsPressedString(" "));
			w.writeLine(c, "Buttons", gamepadAfter.getButtonsPressedString(" "));
			w.writeLine(c, "LT", gamepadBefor.getAnalog(Gamepad::LT));
			w.writeLine(c, "LT", gamepadAfter.getAnalog(Gamepad::LT));
			w.writeLine(c, "RT", gamepadBefor.getAnalog(Gamepad::RT));
			w.writeLine(c, "RT", gamepadAfter.getAnalog(Gamepad::RT));
			w.writeLine(c, "LX", gamepadBefor.getAnalog(Gamepad::LX));
			w.writeLine(c, "LX", gamepadAfter.getAnalog(Gamepad::LX));
			w.writeLine(c, "LY", gamepadBefor.getAnalog(Gamepad::LY));
			w.writeLine(c, "LY", gamepadAfter.getAnalog(Gamepad::LY));
			w.writeLine(c, "RX", gamepadBefor.getAnalog(Gamepad::RX));
			w.writeLine(c, "RX", gamepadAfter.getAnalog(Gamepad::RX));
			w.writeLine(c, "RY", gamepadBefor.getAnalog(Gamepad::RY));
			w.writeLine(c, "RY", gamepadAfter.getAnalog(Gamepad::RY));


		}
			//gamepadVanil.update(0);
			//w.writeLine();
			//w.writeLine(c, "LT", gamepadVanil.getAnalog(Gamepad::LT));
		w.reset();
	}
}

frame DurVisPlugin::interp(std::shared_ptr<frame> f1, std::shared_ptr<frame> f2, float elaps)
{
	float frameDiff = f2->timestamp - f1->timestamp;
	frame newFrame;

	memcpy(&newFrame, f1.get(), sizeof(frame));
	return newFrame;
	//No interpolatioooooooooon
	newFrame.input.ActivateBoost = f1->input.ActivateBoost;
	newFrame.input.Handbrake = f1->input.Handbrake;
	newFrame.input.HoldingBoost = f1->input.HoldingBoost;
	newFrame.input.Jump = f1->input.Jump;
	newFrame.input.Jumped = f1->input.Jumped;
	newFrame.input.DodgeStrafe = f1->input.DodgeStrafe;
	newFrame.input.DodgeForward = f1->input.DodgeForward;
	newFrame.input.Pitch = f1->input.Pitch + ((f2->input.Pitch - f1->input.Pitch) * elaps / frameDiff);
	newFrame.input.Yaw = f1->input.Yaw + ((f2->input.Yaw - f1->input.Yaw) * elaps / frameDiff);
	newFrame.input.Roll = f1->input.Roll + ((f2->input.Roll - f1->input.Roll) * elaps / frameDiff);
	newFrame.input.Throttle = f1->input.Throttle + ((f2->input.Throttle - f1->input.Throttle) * elaps / frameDiff);
	newFrame.input.Steer = f1->input.Steer + ((f2->input.Steer - f1->input.Steer) * elaps / frameDiff);
	return newFrame;
}
