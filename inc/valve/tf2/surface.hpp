//
// Created by Riley on 4/25/2024.
//

#pragma once

#include "memory.hpp"

class c_surface {
public:
  void unlock_cursor() {
    memory::find_vfunc<void(__thiscall*)(void*)>(this, 61u)(this);
  }

  void play_sound(const char* name) {
    memory::find_vfunc<void(__thiscall*)(void*, const char*)>(this, 78u)(this, name);
  }
};

class c_engine_vgui {
public:
  // returns true if the pause menu is visible
  bool is_game_ui_visible() {
    return memory::find_vfunc<bool(__thiscall*)(void*)>(this, 21u)(this);
  }
};

class c_panel {
public:
  const char* get_name(u32 panel) {
    return memory::find_vfunc<const char*(__thiscall*)(void*, u32)>(this, 36u)(this, panel);
  }
};