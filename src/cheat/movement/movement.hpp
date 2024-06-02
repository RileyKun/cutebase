//
// Created by Riley on 4/25/2024.
//

#pragma once

#include "link.hpp"

class c_movement {
public:
  void run(c_user_cmd* cmd);

private:
  void bunnyhop(c_entity* player, c_user_cmd* cmd);
  void auto_strafe(c_entity* player, c_user_cmd* cmd);
};

singleton_feature(movement, c_movement);