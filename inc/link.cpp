//
// Created by Riley on 4/24/2024.
//

#include "link.hpp"

#include <fstream>
#include <filesystem>

void c_ctx::get_user() {

}

bool c_ctx::is_game_focused() {
  return false; // TODO: this function
}

bool c_ctx::get_render_state() {
  return this->do_optimized_render;
}

void c_ctx::set_render_state(bool state) {
  this->do_optimized_render = state;
}

void c_ctx::get_local() {
  this->local_player =
      g_tf2.entity_list->get_client_entity(g_tf2.engine_client->get_local_player())->as<c_entity>();

  if (!local_player)
    return;

  this->local_weapon = local_player->get_active_weapon();
}

color c_ctx::get_health_color(const int health, const int max_health) {
  if (health > max_health)
    return {0.6f, 0.8f, 1.0f, 1.f}; // still not a good color but it will do for now

  const int hp = glm::max(0, glm::min(health, max_health));

  auto      i_r = static_cast<u32>(glm::min((510 * (max_health - hp)) / max_health, 200));
  auto      i_g = static_cast<u32>(glm::min((510 * hp) / max_health, 200));

  auto      f_r = (float)i_r;
  auto      f_g = (float)i_g;

  f_r = f_r / 255.f;
  f_g = f_g / 255.f;

  return {f_r, f_g, 0.f, 1.f};
}

color c_ctx::get_team_color(c_entity* entity) {
  switch (entity->team_num()) {
    case 2:
      return (ImColor&&)TEAM_RED;

    case 3:
      return (ImColor&&)TEAM_BLU;

    default:
      return (ImColor&&)TEAM_SPEC;
  }
}
color c_ctx::get_team_novis_color(c_entity* entity) {
  switch(entity->team_num()){
    case 2:
      return (ImColor&&)TEAM_RED_NOVIS;
    case 3:
      return (ImColor&&)TEAM_BLU_NOVIS;
    default:
      return (ImColor&&)TEAM_SPEC;
  }
}

void c_tf2::get_interfaces() {
  globals = *memory::find_pattern<c_global_vars_base**, 1u>("engine.dll",
                                                            "A1 ? ? ? ? 8B 11 68 ? ? ? ? 50 50 FF 12");
  cvar = memory::find_interface<i_cvar*>("vstdlib.dll", "VEngineCvar004");
  engine_vgui = memory::find_interface<c_engine_vgui*>("engine.dll", "VEngineVGui002");
  material_system = memory::find_interface<c_material_system*>("materialsystem.dll", "VMaterialSystem081");
  input_system = memory::find_interface<c_input_system*>("inputsystem.dll", "InputSystemVersion001");
  input = **memory::find_pattern<i_input***, 2u>("client.dll", "8B 0D ? ? ? ? 56 8B 01 FF 50 ? 5E C7 47");
  client_mode =
      **memory::find_pattern<client_mode_shared***, 2u>("client.dll", "8B 0D ? ? ? ? FF 96 ? ? ? ? 8B 4D");
  client_state = *memory::find_pattern<c_client_state**, 1u>(
      "client.dll", "68 ? ? ? ? E8 ? ? ? ? 83 C4 ? 5F 5E 5B 5D");
  studio_render = memory::find_interface<c_studio_render*>("studiorender.dll", "VStudioRender025");
  model_info_client = memory::find_interface<c_model_info_client*>("engine.dll", "VModelInfoClient006");
  hl_client = memory::find_interface<c_hl_client*>("client.dll", "VClient017");
  engine_client = memory::find_interface<c_engine_client*>("engine.dll", "VEngineClient013");
  entity_list = memory::find_interface<i_client_entity_list*>("client.dll", "VClientEntityList003");
  surface = memory::find_interface<c_surface*>("vguimatsurface.dll", "VGUI_Surface030");
  panel = memory::find_interface<c_panel*>("vgui2.dll", "VGUI_Panel009");
  engine_trace = memory::find_interface<i_engine_trace*>("engine.dll", "EngineTraceClient003");
  move_helper = **memory::find_pattern<i_move_helper***, 2u>("client.dll", "FF 35 ? ? ? ? 50 8B 11");
  prediction = memory::find_interface<c_prediction*>("client.dll", "VClientPrediction001");
}

bool c_tf2::w2s(const vec3& origin, vec2& project) {
  const auto& matrix = g_tf2.engine_client->world_to_screen_matrix();
  const auto  w = glm::dot(matrix[3].xyz(), origin) + matrix[3].w;

  if (w <= 0.001f)
    return false;

  const vec2 clip_space(glm::dot(matrix[0].xyz(), origin) + matrix[0].w,
                        glm::dot(matrix[1].xyz(), origin) + matrix[1].w);

  const auto normalized_space = clip_space / w;

  project.x = 0.5f * (1.f + normalized_space.x) * ((float)ctx->screen_width);
  project.y = 0.5f * (1.f - normalized_space.y) * ((float)ctx->screen_height);

  return true;
}

bool c_tf2::is_projectile_weapon(c_weapon* weapon) {
  switch (weapon->get_weapon_id()) {
    case TF_WEAPON_SYRINGEGUN_MEDIC:
    case TF_WEAPON_ROCKETLAUNCHER:
    case TF_WEAPON_GRENADELAUNCHER:
    case TF_WEAPON_PIPEBOMBLAUNCHER:
    case TF_WEAPON_FLAMETHROWER:
    case TF_WEAPON_FLAREGUN:
    case TF_WEAPON_ROCKETLAUNCHER_DIRECTHIT:
    case TF_WEAPON_CROSSBOW:
    case TF_WEAPON_RAYGUN:
    case TF_WEAPON_PARTICLE_CANNON:
    case TF_WEAPON_DRG_POMSON:
    case TF_WEAPON_FLAREGUN_REVENGE:
    case TF_WEAPON_CLEAVER:
    case TF_WEAPON_CANNON:
    case TF_WEAPON_JAR_MILK:
      return true;
  }
  return false;
}

bool c_tf2::is_hitscan_weapon(c_weapon* weapon) {
  switch (weapon->get_weapon_id()) {
    case TF_WEAPON_SHOTGUN_PRIMARY:
    case TF_WEAPON_SHOTGUN_SOLDIER:
    case TF_WEAPON_SHOTGUN_HWG:
    case TF_WEAPON_SHOTGUN_PYRO:
    case TF_WEAPON_SCATTERGUN:
    case TF_WEAPON_SNIPERRIFLE:
    case TF_WEAPON_MINIGUN:
    case TF_WEAPON_SMG:
    case TF_WEAPON_PISTOL:
    case TF_WEAPON_PISTOL_SCOUT:
    case TF_WEAPON_REVOLVER:
    case TF_WEAPON_HANDGUN_SCOUT_PRIMARY:
    case TF_WEAPON_SODA_POPPER:
    case TF_WEAPON_SNIPERRIFLE_DECAP:
    case TF_WEAPON_CHARGED_SMG:
    case TF_WEAPON_SNIPERRIFLE_CLASSIC:
      return true;
  }
  return false;
}

bool c_tf2::is_melee_weapon(c_weapon* weapon) {
  switch (weapon->get_weapon_id()) {
    case TF_WEAPON_BAT:
    case TF_WEAPON_BAT_WOOD:
    case TF_WEAPON_BOTTLE:
    case TF_WEAPON_CLUB:
    case TF_WEAPON_CROWBAR:
    case TF_WEAPON_KNIFE:
    case TF_WEAPON_FISTS:
    case TF_WEAPON_SHOVEL:
    case TF_WEAPON_WRENCH:
    case TF_WEAPON_BONESAW:
    case TF_WEAPON_SWORD:
    case TF_WEAPON_BAT_FISH:
    case TF_WEAPON_BAT_GIFTWRAP:
      return true;
  }
  return false;
}

bool c_tf2::vis_check(c_entity* skip, const c_entity* ent, const Vector& from, const Vector& to) {
  c_game_trace trace;
  c_trace_filter_hitscan filter;
  filter.skip = skip;
  ray_t ray;
  ray.init(from, to);
  g_tf2.engine_trace->trace_ray(ray, (MASK_SHOT | CONTENTS_GRATE), &filter, &trace);
  if(trace.did_hit())
    return trace.ent && trace.ent == ent;
  return true;
}

std::string_view c_tf2::get_weapon_name(int weapon) {
  // TODO: this function
  return "";
}

void c_tf2::get_signatures() {
  g_sigs->host_should_run =
      memory::find_pattern<DWORD, 1u>("engine.dll", "A1 ? ? ? ? 83 78 ? ? 74 ? A1 ? ? ? ? 83 78 ? ? A1");
  g_sigs->net_time =
      memory::find_pattern<DWORD, 2u>("engine.dll", "8B 0D ? ? ? ? 8D 95 ? ? ? ? 6A ? 6A ? 52 8B 01 FF 90");
  g_sigs->host_frametime_unbounded = memory::find_pattern<DWORD, 4u>(
      "engine.dll",
      "F3 0F 10 05 ? ? ? ? 6A ? C7 45 ? ? ? ? ? C7 45 ? ? ? ? ? C7 45 ? ? ? ? ? C6 45 ? ? 89 45 ? F3 0F 11 "
      "45 ? 8B 01 6A ? 52 FF 90 ? ? ? ? 8B 4D ? C7 45 ? ? ? ? ? 85 C9 74 ? 8B 01 6A ? FF 10 8B 0D");
  g_sigs->host_frametime_stddeviation =
      memory::find_pattern<DWORD>("engine.dll", "F3 0F 10 05 ? ? ? ? 8D 55 ? 8B 0D ? ? ? ? A1");
  g_sigs->is_paused = memory::find_pattern<DWORD>("engine.dll", "80 B9 ? ? ? ? ? 75 ? 80 3D");
}
