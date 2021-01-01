/*
 * Rayman2 Mod Loader.
 * Event system (codes, mods)
 */

#include "pch.h"

static std::vector<ModEvent> modFrameEvents;
static CodeParser codeParser;

static Trampoline* OnFrame_t = nullptr;

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

void __cdecl OnFrame_r() {
	codeParser.processCodeList();
	RaiseEvents(modFrameEvents);
}

void InitMods(const std::string* list, const std::wstring path) {
	
}

void InitCodes(const std::string* list, const std::wstring path) {
	
}

void InitEvents() {
	OnFrame_t = new Trampoline(0x402580, 0x402586, OnFrame_r);
}