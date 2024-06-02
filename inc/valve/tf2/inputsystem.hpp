//
// Created by Riley on 4/25/2024.
//

#pragma once

#include "memory.hpp"

class c_input_system {
public:
  void reset_input_state() {
    memory::find_vfunc<void(__thiscall*)(void*)>(this, 25u)(this);
  }
};