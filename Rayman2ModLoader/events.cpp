/*
 * Rayman2 Mod Loader.
 * Event system (run codes and mod dll exported functions when the event is raised)
 */

#include "pch.h"

std::vector<ModEvent> modFrameEvents;
std::vector<ModEvent> modBeforeRenderEvents;
std::vector<ModEvent> modAfterRenderEvents;

CodeParser codeParser;

Trampoline* _fn_vEngine_t = nullptr; // OnFrame

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

	VoidFunc(original, _fn_vEngine_t->Target());
	original();
}

void __cdecl BeforeRender(uint32_t a1) {
	RaiseEvents(modBeforeRenderEvents);
	j_GLI_DRV_bBeginScene(a1);
}

void __cdecl AfterRender(uint32_t a1) {
	RaiseEvents(modAfterRenderEvents);
	j_GLI_DRV_bEndScene(a1);
}

void InitEvents() {
	_fn_vEngine_t = new Trampoline((int)_fn_vEngine, (int)_fn_vEngine + 0x9, OnFrame);
	WriteCall((void*)0x40AF36, BeforeRender);
	WriteCall((void*)0x40B1C6, AfterRender);
}