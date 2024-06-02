//
// Created by Riley on 4/24/2024.
//

#pragma once

#include "link.hpp"

#include <d3d9.h>
#include <intrin.h>

namespace hooks {

namespace directx {
HRESULT api present(IDirect3DDevice9* device, const RECT* src, const RECT* dest, HWND window,
                    const RGNDATA* dirty);
void        startup();
void        shutdown();
} // namespace directx

namespace prediction {
void vf run_command(registers, c_entity* ent, c_user_cmd* cmd, i_move_helper* move);
void startup();
void shutdown();
}

namespace client {
void __cdecl cl_move(float samples, bool final_tick);
void vf frame_stage_notify(registers, frame_stage stage);
bool vf create_move(registers, float sample_time, c_user_cmd* cmd);
void vf override_view(registers, c_view_setup* setup);
void __cdecl check_for_pure_server_whitelist(void** files);
void    startup();
void    shutdown();
} // namespace client

namespace surface {
void vf set_cursor(registers, unsigned long cursor);
void vf lock_cursor(registers);
void vf paint_traverse(registers, u32 panel, bool repaint, bool force);
void    startup();
void    shutdown();
} // namespace surface

namespace studio {
void vf draw_model(registers, draw_model_results_t* results, draw_model_info_t* info, matrix3x4* bone2world,
                   float* weights, float* delayed, vec3* origin, int flags);
void    startup();
void    shutdown();
} // namespace studio

namespace key_values {
void vf set_int(registers, const char* name, int val);
bool vf is_player_dominated(registers, int index);
void startup();
void shutdown();
}

} // namespace hooks

class c_hook_manager {
public:
  void startup_hooks();
  void shutdown_hooks();
};