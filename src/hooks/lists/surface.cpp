//
// Created by Riley on 4/25/2024.
//

#include "../hooks.hpp"
#include "link.hpp"

#include <safetyhook.hpp>

SafetyHookInline s_cursor{}, l_cursor{}, p_trav{};

void vf hooks::surface::set_cursor(registers, unsigned long cursor){
  if (ctx->menu_open) {
    auto cur = ctx->cursor_status.load();
    switch (cur) {
      case 0: cursor = 2; break;
      case 1: cursor = 3; break;
      case 2: cursor = 12; break;
      case 3: cursor = 11; break;
      case 4: cursor = 10; break;
      case 5: cursor = 9; break;
      case 6: cursor = 8; break;
      case 7: cursor = 14; break;
      case 8: cursor = 13; break;
      default: break;
    }
    return s_cursor.thiscall<void>(ecx, cursor);
  }
  s_cursor.thiscall<void>(ecx, cursor);
}

void vf hooks::surface::lock_cursor(registers){
  if(ctx->menu_open) {
    g_tf2.surface->unlock_cursor();
  } else {
    l_cursor.thiscall<void>(ecx);
  }
}

void vf hooks::surface::paint_traverse(registers, u32 panel, bool repaint, bool force) {
  const auto panel_name = g_tf2.panel->get_name(panel);

  if (HASH_RT(panel_name) == HASH_RT("HudScope"))
    return;

  p_trav.thiscall<void>(ecx, panel, repaint, force);
}


void hooks::surface::startup(){
  s_cursor = safetyhook::create_inline(memory::vfunc_ptr(g_tf2.surface, 51), set_cursor);
  l_cursor = safetyhook::create_inline(memory::vfunc_ptr(g_tf2.surface, 62), lock_cursor);
  p_trav = safetyhook::create_inline(memory::vfunc_ptr(g_tf2.panel, 41), paint_traverse);
}

void hooks::surface::shutdown(){
  s_cursor = {};
  l_cursor = {};
  p_trav = {};
}

