//
// Created by Riley on 4/27/2024.
//

#pragma once

#include "typedefs.hpp"

// FF 35 ? ? ? ? 50 8B 11, 2u
// UPDATE: x-ref "download/user_custom/%c%c/%s.dat"
class i_move_helper {
public:

};

class c_entity;
class c_user_cmd;
class c_prediction {
public:
  u8 pad[8];
  bool in_prediction;
  bool first_time_predicted;
  void run_command(c_entity* ent, c_user_cmd* cmd, i_move_helper* move_helper);
};