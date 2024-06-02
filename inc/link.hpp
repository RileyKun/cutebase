//
// Created by Riley on 4/24/2024.
//

#pragma once

#include "typedefs.hpp"
#include "valve/sdk.hpp"

#include "console/console.hpp"
#include "drawsystem/drawsystem.hpp"
#include <imgui_internal.h>

#include "math.hpp"

#include <atomic>
#include <iterator>
#include <map>
#include <sstream>

class c_ctx {
public:
  // TODO: this really should be atomic
#ifdef _DEBUG
  bool menu_open = false;
#else
  bool menu_open = true;
#endif // _DEBUG

  std::atomic_int cursor_status = ATOMIC_VAR_INIT(2);

  int             screen_width = 0;
  int             screen_height = 0;

  bool            send_packet = false;

  c_entity*       local_player = nullptr;
  c_weapon*       local_weapon = nullptr;

  matrix4x4       matrix = {};

  void            get_user();
  void            get_local();
  color           get_health_color(const int health, const int max_health);

  color           get_team_color(c_entity* entity);
  color           get_team_novis_color(c_entity* entity);

  bool            is_game_focused();
  bool            get_render_state();
  void            set_render_state(bool state);

private:
  bool do_optimized_render = false;
};

class c_tf2 {
public:
  c_hl_client*          hl_client = nullptr;
  c_engine_client*      engine_client = nullptr;
  client_mode_shared*   client_mode = nullptr;
  i_client_entity_list* entity_list = nullptr;
  c_input_system*       input_system = nullptr;
  c_surface*            surface = nullptr;
  c_studio_render*      studio_render = nullptr;
  c_material_system*    material_system = nullptr;
  i_engine_trace*       engine_trace = nullptr;
  i_input*              input = nullptr;
  i_move_helper*        move_helper = nullptr;
  c_prediction*         prediction = nullptr;
  c_model_info_client*  model_info_client = nullptr;
  c_client_state*       client_state = nullptr;
  c_panel*              panel = nullptr;
  c_engine_vgui*        engine_vgui = nullptr;
  i_cvar*               cvar = nullptr;
  c_global_vars_base*   globals = nullptr;

  void                  get_interfaces();
  void                  get_signatures();
  bool                  w2s(const vec3& origin, vec2& project);

  bool                  is_projectile_weapon(c_weapon* weapon);
  bool                  is_hitscan_weapon(c_weapon* weapon);
  bool                  is_melee_weapon(c_weapon* weapon);

  bool vis_check(c_entity* skip, const c_entity* ent, const Vector& from, const Vector& to);

  std::string_view      get_weapon_name(int weapon);
};

class c_config {
public:
  struct {
    bool  bunnyhop = true;
    bool  auto_strafe = true;
    float retrack_speed = 0.5f;
  } movement;

  struct {
    bool optimized_rendering = false;
  } gui;
};

class c_signatures {
public:
  DWORD host_should_run;
  DWORD net_time;
  DWORD host_frametime_unbounded;
  DWORD host_frametime_stddeviation;
  DWORD is_paused;
};

singleton(ctx, c_ctx);
singleton(g_vars, c_config);
singleton(g_draw, c_render_threaded);
singleton(g_console, c_console);
singleton(g_draw_add, c_render);
singleton(drawsystem, c_drawsystem);
singleton(g_sigs, c_signatures);

inline c_tf2 g_tf2{};