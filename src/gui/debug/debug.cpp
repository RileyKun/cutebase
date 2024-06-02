//
// Created by Riley on 4/27/2024.
//

#include "debug.hpp"

#include "link.hpp"

// NOTE: +18 from the first inputted text to maintain perfect alignment
#define DEBUG(y, input) \
g_draw->string(fonts::FONT_SEGOE, 5, y, true, e_text_align::TEXT_LEFT, ImColor(1.f, 1.f, 1.f, 1.f), input);

void c_debug::draw() {
  DEBUG(120, std::format("LocalWeaponID = {}", ctx->local_weapon->get_weapon_id()));
}
