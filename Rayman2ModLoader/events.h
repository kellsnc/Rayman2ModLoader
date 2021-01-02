#pragma once

extern std::vector<ModEvent> modFrameEvents;

void RegisterEvent(std::vector<ModEvent>& eventList, HMODULE module, const char* name);
void InitEvents();