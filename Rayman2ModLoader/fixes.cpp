#include "pch.h"

bool __cdecl CheckPause_r(int param) {
	return true;
}

void InitFixes(const IniGroup* loaderconfig) {
	if (loaderconfig->getBool("PauseWhenInactive", true) == false) {
		WriteJump(CheckPause, CheckPause_r);
	}
}