#pragma once

extern std::vector<ModEvent> modFrameEvents;
extern CodeParser codeParser;

void RegisterEvent(std::vector<ModEvent>& eventList, HMODULE module, const char* name);
void InitEvents();