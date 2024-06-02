//
// Created by Riley on 4/24/2024.
//

#include "factory.hpp"

#include "../hooks/wndproc.hpp"

void c_factory::startup() {
  g_tf2.get_interfaces();

  if (GetModuleHandleA("dxvk_d3d9.dll")) {
    g_console->print(icon_type::CON_ERROR, "Failed to load!");
    MessageBoxA(nullptr,
                "You are currently running with graphics options that cutebase does not support.\nCheck your "
                "launch arguments for -vulkan and try again.",
                "cutebase-error", MB_ICONERROR);
    failed = true;
    return;
  }

  g_tf2.get_signatures();

  Sleep(350);

  g_hooks->startup_hooks();

#ifndef CUTE_DEBUG
  g_tf2.surface->play_sound("vo/medic_mvm_say_ready01.mp3");
#endif
}

void c_factory::shutdown() {
  if (failed)
    return;

  ctx->menu_open = false;
  Sleep(250);
  g_hooks->shutdown_hooks();
}

bool c_factory::should_unload() {
  return GetAsyncKeyState(VK_F6);
}

void c_hook_manager::startup_hooks() {
  using namespace hooks;

  directx::startup();
  surface::startup();
  studio::startup();
  wndproc::startup();
  client::startup();
  key_values::startup();
}

void c_hook_manager::shutdown_hooks() {
  using namespace hooks;

  key_values::shutdown();
  client::shutdown();
  wndproc::shutdown();
  studio::shutdown();
  surface::shutdown();
  directx::shutdown();
}