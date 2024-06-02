//
// Created by Riley on 4/27/2024.
//

#include "input.hpp"

#include "memory.hpp"

int i_input::cam_is_third_person() {
  return memory::find_vfunc<int(__thiscall*)(void*)>(this, 31u)(this);
}

void i_input::cam_to_third_person() {
  memory::find_vfunc<void(__thiscall*)(void*)>(this, 32u)(this);
}

void i_input::cam_to_first_person() {
  memory::find_vfunc<void(__thiscall*)(void*)>(this, 33u)(this);
}
