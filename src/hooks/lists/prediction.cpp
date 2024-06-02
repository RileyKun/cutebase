//
// Created by Riley on 4/28/2024.
//

#include "../hooks.hpp"

#include <safetyhook.hpp>

//#include "aimbot/aimbot.hpp"

SafetyHookInline r_cmd{};

void vf hooks::prediction::run_command(registers, c_entity* ent, c_user_cmd* cmd,
                                    i_move_helper* move) {
  r_cmd.thiscall<void>(ecx, ent, cmd, move);

  //f::aimbot.run(cmd, ent, ctx->local_weapon);
}

void hooks::prediction::startup() {
  r_cmd = safetyhook::create_inline(memory::vfunc_ptr(g_tf2.prediction, 17), run_command);
}

void hooks::prediction::shutdown() {
  r_cmd = {};
}