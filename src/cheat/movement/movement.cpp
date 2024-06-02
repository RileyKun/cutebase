//
// Created by Riley on 4/25/2024.
//

#include "movement.hpp"

void c_movement::run(c_user_cmd* cmd){
  if(ctx->local_player->is_dead())
    return;

  bunnyhop(ctx->local_player, cmd);
  auto_strafe(ctx->local_player, cmd);
}

void c_movement::bunnyhop(c_entity* player, c_user_cmd* cmd){
  if(!g_vars->movement.bunnyhop)
    return;

  auto& buttons = cmd->buttons;
  auto flags = player->flags();
  static bool jump_state = false;

  if(buttons & IN_JUMP) {
    if(!jump_state && !(flags & FL_ONGROUND))
      buttons &= ~IN_JUMP;

    else if(jump_state)
      jump_state = false;
  }

  else if(!jump_state)
    jump_state = true;
}

void c_movement::auto_strafe(c_entity* player, c_user_cmd* cmd) {
  if (!g_vars->movement.auto_strafe)
    return;

  if (player->flags() & FL_ONGROUND || player->flags() & FL_INWATER)
    return;

  if (cmd->buttons & IN_JUMP)
    return;

  if (cmd->buttons & IN_MOVELEFT || cmd->buttons & IN_MOVERIGHT || cmd->buttons & IN_FORWARD ||
      cmd->buttons & IN_BACK) {
    float side_move = cmd->sidemove;
    float forward_move = cmd->forwardmove;

    vec3 forward{}, right{};
    math::angle_vectors(cmd->viewangles, &forward, &right, nullptr);

    forward.z = right.z = 0.f;

    vec3 forward_normalized = glm::normalize(forward);
    vec3 right_normalized = glm::normalize(right);

    vec3 wish_dir{};
    math::vector_angles({(forward_normalized.x * forward_move) + (right_normalized.x * side_move),
                         (forward_normalized.y * forward_move) + (right_normalized.y * side_move), 0.0f},
                        wish_dir);

    vec3 cur_dir{};
    math::vector_angles(ctx->local_player->velocity(), cur_dir);

    float dir_delta = math::normalize(wish_dir.y - cur_dir.y);
    float turn_scale = math::remap_val_clamped(g_vars->movement.retrack_speed, 0.f, 1.f, 0.9f, 1.f);
    float rotation = DEG2RAD((dir_delta > 0.0f ? -90.0f : 90.f) + (dir_delta * turn_scale));

    float cos_rotation = cosf(rotation);
    float sin_rotation = sinf(rotation);

    cmd->forwardmove = (cos_rotation * forward_move) - (sin_rotation * side_move);
    cmd->sidemove = (sin_rotation * forward_move) + (cos_rotation * side_move);
  }
}
