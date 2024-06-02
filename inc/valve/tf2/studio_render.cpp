//
// Created by Riley on 4/27/2024.
//

#include "studio_render.hpp"

#include "memory.hpp"

void c_studio_render::set_color_modulation(const float* color) {
  memory::find_vfunc<void(__thiscall*)(void*, const float*)>(this, 27)(this, color);
}

void c_studio_render::set_alpha_modulation(float alpha) {
  memory::find_vfunc<void(__thiscall*)(void*, float)>(this, 28)(this, alpha);
}

void c_studio_render::forced_material_override(i_material* material, override_type_t override_type) {
  memory::find_vfunc<void(__thiscall*)(void*, i_material*, override_type_t)>(this, 33)(this, material,
                                                                                       override_type);
}

void i_material::set_material_var_flag(material_var_flags_t flag, bool state) {
  memory::find_vfunc<void(__thiscall*)(void*, material_var_flags_t, bool)>(this, 29)(this, flag, state);
}

i_material* c_material_system::find_material(std::string_view name, std::string_view group, bool complain,
                                             const char* complain_prefix) {
  return memory::find_vfunc<i_material*(__thiscall*)(void*, const char*, const char*, bool, const char*)>(
      this, 73u)(this, name.data(), group.data(), complain, complain_prefix);
}

model_t* c_model_info_client::get_model(int entidx) {
  return memory::find_vfunc<model_t*(__thiscall*)(void*, int)>(this, 1u)(this, entidx);
}

studiohdr_t* c_model_info_client::get_studio_model(const model_t* model) {
  return memory::find_vfunc<studiohdr_t*(__thiscall*)(void*, const model_t*)>(this, 28u)(this, model);
}
