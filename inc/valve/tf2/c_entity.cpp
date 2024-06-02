//
// Created by Riley on 4/27/2024.
//

#include "link.hpp"
#include "c_entity.hpp"

c_weapon* c_entity::get_active_weapon() {
  if (active_weapon())
    return g_tf2.entity_list->get_client_entity_from_handle(this->active_weapon())->as<c_weapon>();

  return nullptr;
}

vec3 c_entity::get_hitbox_position(const int hitbox, const vec3 offset) {
  const auto& model = get_model();
  if(!model)
    return vec3();
  const auto& hdr = g_tf2.model_info_client->get_studio_model(model);
  if(!hdr)
    return vec3();
  const auto& set = hdr->get_hitbox_set(hitbox_set());
  if(!set)
    return vec3();
  matrix3x4 matrix[128];
  if(!setup_bones(matrix, 128, BONE_USED_BY_ANYTHING, sim_time()))
    return vec3();
  const auto& box = set->pHitbox(hitbox);
  if(!box)
    return vec3();
  Vector out;
  math::vector_transform(offset, matrix[box->bone], out);
  return out;
}
int c_entity::get_num_of_hitboxes() {
  const auto& model = get_model();
  if(!model) return 0;
  const auto& hdr = g_tf2.model_info_client->get_studio_model(model);
  if(!hdr) return 0;
  const auto& set = hdr->get_hitbox_set(hitbox_set());
  if(!set) return 0;

  return set->numhitboxes;
}
