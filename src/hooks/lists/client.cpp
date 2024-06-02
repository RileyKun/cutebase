//
// Created by Riley on 4/25/2024.
//

#include "../hooks.hpp"

#include "../../gui/gui.hpp"
#include <safetyhook.hpp>

#include "link.hpp"
#include "movement/movement.hpp"

SafetyHookInline fs{}, cr_move{}, c_move{}, o_view{}, pure{};

void vf          hooks::client::frame_stage_notify(registers, frame_stage stage) {
  fs.thiscall<void>(ecx, stage);

  switch (stage) {
    case FRAME_UNDEFINED:
    case FRAME_START:
    case FRAME_NET_UPDATE_START:
    case FRAME_NET_UPDATE_POSTDATAUPDATE_START:
      break;
    case FRAME_NET_UPDATE_POSTDATAUPDATE_END: {
      ctx->get_local();
      break;
    }
    case FRAME_NET_UPDATE_END:
      break;
    case FRAME_RENDER_START: {
      if (!ctx->screen_width || !ctx->screen_height)
        break;

      ctx->set_render_state(g_vars->gui.optimized_rendering);

      cutegui::watermark->draw();

      g_draw->flush();
      break;
    }
    case FRAME_RENDER_END:
    default:
      break;
  }
}

bool vf hooks::client::create_move(registers, float sample_time, c_user_cmd* cmd) {
  const auto result = cr_move.thiscall<bool>(ecx, sample_time, cmd);

  if (!cmd->command_number) // do not let createmove run every frame
    return result;

  if (result) {
    g_tf2.engine_client->set_view_angles(cmd->viewangles);
  }

  // TODO: randomseed

  if (ctx->local_player) {
    f::movement.run(cmd);

    // TODO: allocate temp command, set pred and call runcommand
  }

  // prevent createmove from snapping view angles
  return false;
}

void send_move() {
  if (!g_tf2.client_state || !g_tf2.client_state->m_NetChannel)
    return;

  byte      data[MAX_CMD_BUFFER];
  const int choked = ((CNetChannel*)g_tf2.client_state->m_NetChannel)->ChokedPackets;
  const int next_cmd_num = g_tf2.client_state->lastoutgoingcommand + choked + 1;

  // send the client update packet
  CLC_Move  move_msg;

  move_msg.m_DataOut.StartWriting(data, sizeof(data));

  // how many real new commands are queued up
  move_msg.m_nNewCommands = 1 + choked;
  move_msg.m_nNewCommands = math::clamp(move_msg.m_nBackupCommands, 0, MAX_NEW_COMMANDS);

  // determine number of backup commands to send along
  const int extra_cmds = (choked + 1) - move_msg.m_nNewCommands;
  const int backup_cmds = std::max(2, extra_cmds);
  move_msg.m_nBackupCommands = math::clamp(backup_cmds, 0, MAX_BACKUP_COMMANDS);

  const int num_cmds = move_msg.m_nNewCommands + move_msg.m_nBackupCommands;

  int       from = -1; // first command is deltaed against zeros
  bool      ok = true;
  for (auto to = next_cmd_num - num_cmds + 1; to <= next_cmd_num; to++) {
    const bool is_new_cmd = to >= next_cmd_num - move_msg.m_nNewCommands + 1;
    // first valid command number is 1
    ok = ok && g_tf2.hl_client->write_cmd_to_buffer(&move_msg.m_DataOut, from, to, is_new_cmd);
    from = to;
  }

  if (ok) {
    if (extra_cmds) {
      ((CNetChannel*)g_tf2.client_state->m_NetChannel)->ChokedPackets -= extra_cmds;
    }
    // only write message if all usercmds were written correctly, otherwise parsing would fail
    memory::find_vfunc<bool(__thiscall*)(void*, INetMessage*, bool, bool)>(
        g_tf2.client_state->m_NetChannel, 37)(g_tf2.client_state->m_NetChannel, &move_msg, false, false);
  }
}

void __cdecl hooks::client::cl_move(float samples, bool final_tick) {
  c_move.call<void>(samples, final_tick);
}

void vf hooks::client::override_view(registers, c_view_setup* setup) {
  o_view.thiscall<void>(ecx, setup);
}

void __cdecl hooks::client::check_for_pure_server_whitelist(void** files) {
}

void hooks::client::startup() {
  pure = safetyhook::create_inline(
      memory::find_pattern<DWORD>("engine.dll", "55 8B EC 83 EC ? 83 3D ? ? ? ? ? 0F 8E"),
      check_for_pure_server_whitelist);
  fs = safetyhook::create_inline(memory::vfunc_ptr(g_tf2.hl_client, 35), frame_stage_notify);
  cr_move = safetyhook::create_inline(memory::vfunc_ptr(g_tf2.client_mode, 21), create_move);
  c_move = safetyhook::create_inline(
      memory::find_pattern<DWORD>("engine.dll", "55 8B EC B8 ? ? ? ? E8 ? ? ? ? 83 3D ? ? ? ? ? 0F 8C"),
      reinterpret_cast<void*>(cl_move));
  o_view = safetyhook::create_inline(memory::vfunc_ptr(g_tf2.client_mode, 16), override_view);
}

void hooks::client::shutdown() {
  pure = {};
  fs = {};
  cr_move = {};
  o_view = {};
  c_move = {};
}
