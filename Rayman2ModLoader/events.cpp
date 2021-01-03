/*
 * Rayman2 Mod Loader.
 * Event system (run codes and mod dll exports)
 */

#include "pch.h"

std::vector<ModEvent> modFrameEvents;
CodeParser codeParser;

void RaiseEvents(const std::vector<ModEvent>& eventList) {
	for (auto& i : eventList) {
		i();
	}
}

void RegisterEvent(std::vector<ModEvent>& eventList, HMODULE module, const char* name) {
	const auto modEvent = reinterpret_cast<const ModEvent>(GetProcAddress(module, name));

	if (modEvent != nullptr) {
		eventList.push_back(modEvent);
	}
}

void __cdecl OnFrame(int a1) {
	codeParser.processCodeList();
	RaiseEvents(modFrameEvents);
}

void InitEvents() {
	WriteJump((void*)0x402564, OnFrame);
	WriteJump((void*)0x402570, OnFrame);
}