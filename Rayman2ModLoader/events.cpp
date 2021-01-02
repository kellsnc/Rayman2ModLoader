/*
 * Rayman2 Mod Loader.
 * Event system (codes, mods)
 */

#include "pch.h"

std::vector<ModEvent> modFrameEvents;

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

void __cdecl OnFrame_r(tagMSG* msg) {
	codeParser.processCodeList();
	RaiseEvents(modFrameEvents);

	void(__cdecl * Original)(tagMSG * msg) = (void(__cdecl*)(tagMSG * msg))OnFrame_t->Target();
	Original(msg);
}

void InitEvents() {
	OnFrame_t = new Trampoline(0x402580, 0x402586, OnFrame_r);
}