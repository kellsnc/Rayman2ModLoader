/*
 * Rayman2 Mod Loader.
 * Event system (run codes and mod dll exports)
 */

#include "pch.h"

std::vector<ModEvent> modFrameEvents;
std::vector<ModEvent> modBeforeRenderEvents;
std::vector<ModEvent> modAfterRenderEvents;
CodeParser codeParser;

Trampoline* GameEngine_t = nullptr; // OnFrame

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

void __cdecl OnFrame() {
	codeParser.processCodeList();
	RaiseEvents(modFrameEvents);

	VoidFunc(original, GameEngine_t->Target());
	original();
}

void __cdecl BeforeRender(Uint32 a1) {
	RaiseEvents(modBeforeRenderEvents);
	j_Glide_OnSceneBegin(a1);
}

void __cdecl AfterRender() {
	RaiseEvents(modAfterRenderEvents);
	j_Glide_OnSceneEnd();
}

void InitEvents() {
	GameEngine_t = new Trampoline((int)GameEngine, (int)GameEngine + 0x9, OnFrame);
	WriteCall((void*)0x40AF36, BeforeRender);
	WriteCall((void*)0x40B1C6, AfterRender);
}