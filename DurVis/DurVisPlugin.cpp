#include "DurVisPlugin.h"

#include "bakkesmod/wrappers/GameEvent/ServerWrapper.h"
#include "bakkesmod/wrappers/GameObject/CarWrapper.h"
#include "bakkesmod/wrappers/ArrayWrapper.h"
#include "bakkesmod/wrappers/GameEvent/TutorialWrapper.h"
//#include "bakkesmod/plugin/bakkesmodplugin.h"

#include "SharedMemory.h"
#include "DurVisGamepad.h"

#include "RgbaColor.h"
#include "AnalogDrawer.h"
#include "GraphDrawer.h"
#include "TextDrawer.h"

BAKKESMOD_PLUGIN(DurVisPlugin, "DurVis plugin", "1.0", PLUGINTYPE_FREEPLAY | PLUGINTYPE_CUSTOM_TRAINING)

RgbaColor colorBg = RgbaColor(5, 5, 5, 180);
RgbaColor colorTextBg = RgbaColor(255, 255, 255, 150);
RgbaColor colorGame = RgbaColor(50, 200, 50, 255);
RgbaColor colorGraph = RgbaColor(200, 100, 200, 180);
RgbaColor colorBefor = RgbaColor(255, 50, 50, 255);
RgbaColor colorAfter = RgbaColor(100, 100, 255, 255);
RgbaColor colorBeforB = RgbaColor(200, 200, 80, 200);
RgbaColor colorAfterB = RgbaColor(80, 200, 200, 200);
RgbaColor colorFrame = RgbaColor(255, 255, 255, 150);

TextDrawer text = TextDrawer({ 10, 380 }, colorTextBg, 90, 14);
AnalogDrawer gos = AnalogDrawer({ 10, 320 }, 100, 50, 2);
AnalogDrawer turns = AnalogDrawer({ 10 + 105, 100 + 105 }, 210, 210, 10);
GraphDrawer durs = GraphDrawer(colorGraph, { 260, 100 }, 480);

DurVisGamepad padBefor = DurVisGamepad();
DurVisGamepad padAfter = DurVisGamepad();

SharedMemory duraznoSharedMemory = SharedMemory();

void DurVisPlugin::onLoad() {
    enabled = make_shared<bool>(true);
    drawGraph = make_shared<bool>(true);
    port = make_shared<int>(0);
    cvarManager->registerCvar("durvis_enabled", "1", "Render DurVis", true, true, 0, true, 1).bindTo(enabled);
    cvarManager->registerCvar("durvis_graph", "1", "Render Graph", true, true, 0, true, 1).bindTo(drawGraph);
    cvarManager->registerCvar("durvis_xinputport", "0", "XInput port", true, true, 0, true, 3).bindTo(port);

    gameWrapper->HookEvent("Function TAGame.GameEvent_Tutorial_TA.OnInit", bind(&DurVisPlugin::OnLoadSuitableGameMode, this, std::placeholders::_1));
    gameWrapper->HookEvent("Function TAGame.GameEvent_Tutorial_TA.Destroyed", bind(&DurVisPlugin::OnUnloadSuitableGameMode, this, std::placeholders::_1));
    gameWrapper->HookEvent("Function TAGame.GameEvent_TrainingEditor_TA.StartPlayTest", bind(&DurVisPlugin::OnLoadSuitableGameMode, this, std::placeholders::_1));
    gameWrapper->HookEvent("Function TAGame.GameEvent_TrainingEditor_TA.Destroyed", bind(&DurVisPlugin::OnUnloadSuitableGameMode, this, std::placeholders::_1));

    gameWrapper->HookEvent("Function TAGame.OnlineGameJoinGame_TA.OnInit", bind(&DurVisPlugin::OnUnloadSuitableGameMode, this, std::placeholders::_1));

    duraznoSharedMemory.SetServing(true);
    gameWrapper->RegisterDrawable(std::bind(&DurVisPlugin::Render, this, std::placeholders::_1));
}

void DurVisPlugin::onUnload() {
    duraznoSharedMemory.SetServing(false);
}

void DurVisPlugin::OnLoadSuitableGameMode(std::string eventName) {
    duraznoSharedMemory.SetServing(true);
    gameWrapper->RegisterDrawable(std::bind(&DurVisPlugin::Render, this, std::placeholders::_1));
}

void DurVisPlugin::OnUnloadSuitableGameMode(std::string eventName) {
    duraznoSharedMemory.SetServing(false);
    gameWrapper->UnregisterDrawables();
}

void DurVisPlugin::Render(CanvasWrapper c) {
    if (*enabled && gameWrapper->IsInGame()) {
        auto players = gameWrapper->GetGameEventAsServer().GetCars();

        if (players.Get(0).IsNull() )
            return;

        ControllerInput ci = players.Get(0).GetInput();

        turns.DrawStickFrame(c, colorFrame);

        gos.DrawThrottle(c, colorGame, { 0, 20 }, ci.Throttle);

        turns.DrawSingleAxis(c, colorGame, true, ci.Steer);
        turns.DrawSingleAxis(c, colorGame, true, ci.Yaw);
        turns.DrawSingleAxis(c, colorGame, false, ci.Pitch);
        turns.DrawSingleAxis(c, colorGame, true, ci.Roll);

        text.WriteLine(c, colorGame, "Throttle", to_string(ci.Throttle));
        text.WriteLine(c, colorGame, "Steer", to_string(ci.Steer));
        text.WriteLine(c, colorGame, "Yaw", to_string(ci.Yaw));
        text.WriteLine(c, colorGame, "Pitch", to_string(ci.Pitch));
        text.WriteLine(c, colorGame, "Roll", to_string(ci.Roll));

        // text.WriteLine(c, colorGame, "DodgeForward", to_string(ci.DodgeForward));
        // text.WriteLine(c, colorGame, "DodgeStrafe", to_string(ci.DodgeStrafe));
        // text.WriteLine(c, colorGame, "Jump", to_string(ci.Jump));
        // text.WriteLine(c, colorGame, "Jumped", to_string(ci.Jumped));
        // text.WriteLine(c, colorGame, "ActivateBoost", to_string(ci.ActivateBoost));
        // text.WriteLine(c, colorGame, "HoldingBoost", to_string(ci.HoldingBoost));
        // text.WriteLine(c, colorGame, "Handbrake", to_string(ci.Handbrake));

        if (duraznoSharedMemory.IsMapped()) {
            padBefor.Update(duraznoSharedMemory.GetGamepadStateBefor(*port));
            padAfter.Update(duraznoSharedMemory.GetGamepadStateAfter(*port));

            if (*drawGraph)
                durs.Draw(c, duraznoSharedMemory.GetDuration(*port));

            gos.DrawThrottle(c, colorBefor, { 0, 0 }, padBefor.GetTrigger(Analog::LT));
            gos.DrawThrottle(c, colorAfter, { 0, 10 }, padAfter.GetTrigger(Analog::LT));
            gos.DrawThrottle(c, colorBefor, { 0, 30 }, padBefor.GetTrigger(Analog::RT));
            gos.DrawThrottle(c, colorAfter, { 0, 40 }, padAfter.GetTrigger(Analog::RT));

            turns.DrawDualAxis(c, colorBefor, padBefor.GetStick(Analog::LX), padBefor.GetStick(Analog::LY));
            turns.DrawDualAxis(c, colorAfter, padAfter.GetStick(Analog::LX), padAfter.GetStick(Analog::LY));

            turns.DrawDualAxis(c, colorBeforB, padBefor.GetStick(Analog::RX), padBefor.GetStick(Analog::RY));
            turns.DrawDualAxis(c, colorAfterB, padAfter.GetStick(Analog::RX), padAfter.GetStick(Analog::RY));

            text.WriteLine();
            // w.WriteLine(c, colorBefor, "=Before");
            // w.WriteLine(c, colorAfter, "=After");
            text.WriteTrigger(c, colorBefor, "Left Trigger", padBefor.GetTrigger(Analog::LT));
            text.WriteTrigger(c, colorAfter, "LT", padAfter.GetTrigger(Analog::LT));
            text.WriteTrigger(c, colorBefor, "RT", padBefor.GetTrigger(Analog::RT));
            text.WriteTrigger(c, colorAfter, "RT", padAfter.GetTrigger(Analog::RT));
            text.WriteStick(c, colorBefor, "Left Stick X", padBefor.GetStick(Analog::LX));
            text.WriteStick(c, colorAfter, "LX", padAfter.GetStick(Analog::LX));
            text.WriteStick(c, colorBefor, "LY", padBefor.GetStick(Analog::LY));
            text.WriteStick(c, colorAfter, "LY", padAfter.GetStick(Analog::LY));
            text.WriteStick(c, colorBefor, "RX", padBefor.GetStick(Analog::RX));
            text.WriteStick(c, colorAfter, "RX", padAfter.GetStick(Analog::RX));
            text.WriteStick(c, colorBefor, "RY", padBefor.GetStick(Analog::RY));
            text.WriteStick(c, colorAfter, "RY", padAfter.GetStick(Analog::RY));
            text.WriteLine();
            text.WriteLine(c, colorBefor, "Buttons", padBefor.GetButtonsPressedString(" "));
            text.WriteLine(c, colorAfter, "Buttons", padAfter.GetButtonsPressedString(" "));
        } else {
            text.WriteLine(c, colorBefor, "Durazno^2 not found");
        }

        text.Reset();
    }
}
