//
// Created by Riley on 4/28/2024.
//

#include "prediction.hpp"

#include "memory.hpp"

void c_prediction::run_command(c_entity* ent, c_user_cmd* cmd, i_move_helper* move_helper) {
  memory::find_vfunc<void(__thiscall*)(void*, c_entity*, c_user_cmd*, i_move_helper*)>(this, 17u)(
      this, ent, cmd, move_helper);
}
