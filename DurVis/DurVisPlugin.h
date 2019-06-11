#pragma once
#include <string>
#pragma comment(lib, "bakkesmod.lib")
#include "bakkesmod/plugin/bakkesmodplugin.h"

class DurVisPlugin : public BakkesMod::Plugin::BakkesModPlugin {
public:
    virtual void onLoad();
    virtual void onUnload();
    void OnLoadSuitableGameMode(std::string eventName);
    void OnUnloadSuitableGameMode(std::string eventName);
    void Render(CanvasWrapper canvas);
private:
    std::shared_ptr<bool> enabled;
    std::shared_ptr<bool> drawGraph;
    std::shared_ptr<int> port;
};
