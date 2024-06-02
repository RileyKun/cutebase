//
// Created by Riley on 4/24/2024.
//

#include "factory/factory.hpp"

DWORD api entry(void* arg) {
#ifdef _DEBUG
  g_console->spawn("cutebase");
#endif // _DEBUG
  g_console->print(icon_type::CON_OK, "Initialized.");

  while (!GetModuleHandleA("GameUI.dll"))
    Sleep(15000);

  factory->startup();

  while (!factory->should_unload())
    Sleep(500);

  g_console->print(icon_type::CON_STAGE, "Unload requested...");

  factory->shutdown();

  g_console->print(icon_type::CON_OK, "Unloaded!");

  Sleep(1000);

  g_console->kill();
  Sleep(50);

  FreeLibraryAndExitThread((HMODULE)arg, 0);
}

DWORD api exit() {
  factory->shutdown();
  return 0;
}

i32 api DllMain(HMODULE inst, DWORD reason, void* arg) {
  switch (reason) {
    case DLL_PROCESS_ATTACH: {
      auto thread = CreateThread(nullptr, 0, entry, inst, 0, nullptr);
      if (!thread)
        return 0;
      CloseHandle(thread);
      return 1;
    }
    case DLL_PROCESS_DETACH: {
      exit();
      return 1;
    }
    default:
      return 1;
  }
}