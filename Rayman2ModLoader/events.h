#pragma once

extern std::vector<ModEvent> modFrameEvents;
extern std::vector<ModEvent> modBeforeRenderEvents;
extern std::vector<ModEvent> modAfterRenderEvents;
extern CodeParser codeParser;

void RegisterEvent(std::vector<ModEvent>& eventList, HMODULE module, const char* name);
void InitEvents();