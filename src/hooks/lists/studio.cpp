//
// Created by Riley on 4/27/2024.
//

#include "../hooks.hpp"
#include "link.hpp"

#include <safetyhook.hpp>

SafetyHookInline dmod{};

// TODO: Pixy; recode this, this has completely dog shit logic that I hate
void vf hooks::studio::draw_model(registers, draw_model_results_t* results, draw_model_info_t* info,
                                           matrix3x4* bone2world, float* weights, float* delayed, vec3* origin,
                                           int flags) {
  dmod.thiscall<void>(ecx, results, info, bone2world, weights, delayed, origin, flags);
}

void hooks::studio::startup() {
  dmod = safetyhook::create_inline(memory::vfunc_ptr(g_tf2.studio_render, 29), draw_model);
}

void hooks::studio::shutdown() {
  dmod = {};
}