/*
 * Rayman2 Mod Loader.
 * Event system (codes, mods)
 */

#include "pch.h"

std::vector<ModEvent> modFrameEvents;
CodeParser codeParser;

void RaiseEvents(const std::vector<ModEvent>& eventList)
{
	for (auto& i : eventList)
		i();
}

void RegisterEvent(std::vector<ModEvent>& eventList, HMODULE module, const char* name) {
	const auto modEvent = reinterpret_cast<const ModEvent>(GetProcAddress(module, name));

	if (modEvent != nullptr)
	{
		eventList.push_back(modEvent);
	}
}

void __cdecl OnFrame() {
	codeParser.processCodeList();
}

void InitMods(const std::string* list, const std::wstring path) {
	
}

void InitCodes(const std::string* list, const std::wstring path) {
	
}

void InitEvents() {
	
}