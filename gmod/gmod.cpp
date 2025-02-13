﻿#include <thread>

#include "memory.hpp"

#include "hooks.hpp"
#include "menu/menu.hpp"

void entry_point() {
	hooks::initialize_hooks();
	menu::InitializeMenu();
}

BOOL APIENTRY DllMain(HINSTANCE dll_instance, DWORD reason, LPVOID reversed) {
	memory::dllinstance = dll_instance;
	DisableThreadLibraryCalls(dll_instance);
	if (reason == DLL_PROCESS_ATTACH) {
		std::thread(entry_point).detach();
	}
	return TRUE;
}