//
// Created by Riley on 4/25/2024.
//

#include "cdll_int.hpp"

#include "bitbuf.hpp" // im scared of what the compiler will say

client_class* c_hl_client::get_all_classes(void) {
  return memory::find_vfunc<client_class*(__thiscall*)(void*)>(this, 8u)(this);
}

void c_hl_client::create_move(float sample_time, bool active) {
  memory::find_vfunc<void(__thiscall*)(void*, float, bool)>(this, 21u)(this, sample_time, active);
}

bool c_hl_client::write_cmd_to_buffer(bf_write* buf, int from, int to, bool is_new_cmd) {
  return memory::find_vfunc<bool(__thiscall*)(void*, bf_write*, int from, int to, bool is_new_cmd)>(
      this, 23u)(this, buf, from, to, is_new_cmd);
}

void c_engine_client::get_screen_size(int& w, int& h) {
  memory::find_vfunc<void(__thiscall*)(void*, int&, int&)>(this, 5u)(this, w, h);
}

void c_engine_client::client_cmd(const char* input) {
  return memory::find_vfunc<void(__thiscall*)(void*, const char*)>(this, 12u)(this, input);
}

void c_engine_client::client_cmd_unrestricted(const char* input) {
  // 100 something i don't know
  // TODO: this function
}

int c_engine_client::get_local_player(void) {
  return memory::find_vfunc<int(__thiscall*)(void*)>(this, 12u)(this);
}

float c_engine_client::plat_float_time(void) {
  return memory::find_vfunc<float(__thiscall*)(void*)>(this, 14u)(this);
}

void c_engine_client::get_view_angles(QAngle& va) {
  memory::find_vfunc<void(__thiscall*)(void*, QAngle&)>(this, 19u)(this, va);
}

void c_engine_client::set_view_angles(QAngle& va) {
  memory::find_vfunc<void(__thiscall*)(void*, QAngle&)>(this, 20u)(this, va);
}

int c_engine_client::get_max_clients(void) {
  return memory::find_vfunc<int(__thiscall*)(void*)>(this, 21u)(this);
}

bool c_engine_client::is_in_game(void) {
  return memory::find_vfunc<bool(__thiscall*)(void*)>(this, 26u)(this);
}

bool c_engine_client::is_connected(void) {
  return memory::find_vfunc<bool(__thiscall*)(void*)>(this, 27u)(this);
}

const char* c_engine_client::get_game_directory(void) {
  return memory::find_vfunc<const char*(__thiscall*)(void*)>(this, 35u)(this);
}

const matrix4x4& c_engine_client::world_to_screen_matrix(void) {
  return memory::find_vfunc<const matrix4x4&(__thiscall*)(void*)>(this, 36u)(this);
}

bool c_engine_client::get_player_info(int entidx, player_info_t* info) {
  return memory::find_vfunc<bool(__thiscall*)(void*, int, player_info_t*)>(this, 8u)(this, entidx, info);
}
