#pragma once

#include "cdll_int.hpp"
#include "client_entity.hpp"
#include "constants.hpp"
#include "netvars/netvars.hpp"

#include "memory.hpp"

class c_weapon; // forward declare for get_active_weapon
class c_entity : public i_client_entity {
public:
  netvar(is_dead, bool, "DT_BasePlayer", "deadflag");
  netvar(flags, int, "DT_BasePlayer", "m_fFlags");
  netvar(mins, vec3, "DT_BaseEntity", "m_vecMins");
  netvar(maxs, vec3, "DT_BaseEntity", "m_vecMaxs");
  netvar(sim_time, float, "DT_BaseEntity", "m_flSimulationTime");
  netvar(origin, vec3, "DT_BaseEntity", "m_vecOrigin");
  netvar(health, int, "DT_BasePlayer", "m_iHealth");
  netvar(observer_mode, int, "DT_BasePlayer", "m_iObserverMode");
  netvar(observer_target, c_base_handle, "DT_BasePlayer", "m_hObserverTarget");
  netvar(velocity, vec3, "DT_BasePlayer", "m_vecVelocity[0]");
  netvar(view_offset, vec3, "DT_BasePlayer", "m_vecViewOffset[0]");
  netvar(team_num, int, "DT_BaseEntity", "m_iTeamNum");
  netvar(upgrade_level, int, "DT_BaseObject", "m_iUpgradeLevel");
  netvar(is_mini_building, bool, "DT_BaseObject", "m_bMiniBuilding");
  netvar(active_weapon, int, "DT_BaseCombatCharacter", "m_hActiveWeapon");
  netvar(_condition_bits, int, "DT_TFPlayer", "_condition_bits");
  netvar(player_cond, int, "DT_TFPlayer", "m_nPlayerCond");
  netvar(player_cond_ex, int, "DT_TFPlayer", "m_nPlayerCondEx");
  netvar(player_cond_ex2, int, "DT_TFPlayer", "m_nPlayerCondEx2");
  netvar(player_cond_ex3, int, "DT_TFPlayer", "m_nPlayerCondEx3");
  netvar(player_cond_ex4, int, "DT_TFPlayer", "m_nPlayerCondEx4");
  netvar(force_taunt_cam, int, "DT_TFPlayer", "m_nForceTauntCam");
  netvar(kills, int, "DT_TFPlayer", "m_iKills");
  netvar(deaths, int, "DT_TFPlayer", "m_iDeaths");
  netvar(fov, int, "DT_BasePlayer", "m_iFOV");
  netvar(hitbox_set, int, "DT_BaseAnimating", "m_nHitboxSet");

  bool in_cond(const ETFCond cond) {
    const int _cond = static_cast<int>(cond);

    switch (_cond / 32) {
      case 0: {
        const int bit = (1 << _cond);

        if ((player_cond() & bit) == bit || (_condition_bits() & bit) == bit)
          return true;

        break;
      }

      case 1: {
        const int bit = 1 << (_cond - 32);

        if ((player_cond_ex() & bit) == bit)
          return true;

        break;
      }

      case 2: {
        const int bit = 1 << (_cond - 64);

        if ((player_cond_ex2() & bit) == bit)
          return true;

        break;
      }

      case 3: {
        const int bit = 1 << (_cond - 96);

        if ((player_cond_ex3() & bit) == bit)
          return true;

        break;
      }

      case 4: {
        const int bit = 1 << (_cond - 128);

        if ((player_cond_ex4() & bit) == bit)
          return true;

        break;
      }

      default:
        break;
    }

    return false;
  }
  bool is_burning() { return in_cond(ETFCond::TF_COND_BURNING) || in_cond(ETFCond::TF_COND_BURNING_PYRO); }
  bool has_high_kd() {
    if ((float)kills() / (float)deaths() > 15.f)
      return true;

    return false;
  }
  bool is_critboosted() {
    int cond = player_cond();
    int cond_ex = player_cond_ex();

    return cond & TFCond_Kritzkrieged || _condition_bits() & TFCond_Kritzkrieged ||
           cond_ex & TFCondEx_CritCanteen || cond_ex & TFCondEx_CritOnFirstBlood ||
           cond_ex & TFCondEx_CritOnWin || cond_ex & TFCondEx_CritOnKill ||
           cond_ex & TFCondEx_CritDemoCharge || cond_ex & TFCondEx_CritOnFlagCapture ||
           cond_ex & TFCondEx_HalloweenCritCandy || cond_ex & TFCondEx_PyroCrits;
  }
  bool is_mini_critboosted() { return player_cond() & TFCond_MiniCrits; }
  bool is_bonked() { return player_cond() & TFCond_Bonked; }
  bool is_charging() { return player_cond() & TFCond_Charging; }
  bool is_taunting() { return player_cond() & TFCond_Taunting; }
  bool is_marked() {
    return player_cond() & TFCond_Jarated || player_cond() & TFCond_MarkedForDeath ||
           player_cond_ex() & TFCondEx_MarkedForDeathSilent;
  }
  bool is_stunned() { return player_cond() & TFCond_Stunned; }
  bool is_in_kart() { return player_cond_ex() & TFCondEx_InKart; }
  bool is_ghost() { return player_cond_ex2() & TFCondEx2_HalloweenGhostMode; }
  bool is_cloaked() {
    return player_cond() & TFCond_Cloaked || player_cond() & TFCond_CloakFlicker ||
           player_cond_ex2() & TFCondEx2_Stealthed || player_cond_ex2() & TFCondEx2_StealthedUserBuffFade;
  }
  bool is_invuln() {
    return player_cond() & TFCond_Ubercharged || player_cond_ex() & TFCondEx_UberchargedCanteen;
  }
  bool is_zoomed() { return player_cond() & TFCond_Zoomed; }
  bool is_quickfix_ubered() { return player_cond() & TFCond_MegaHeal; }
  bool is_in_conch() { return player_cond() & TFCond_RegenBuffed; }
  bool is_in_backup() { return player_cond() & TFCond_DefenseBuffed; }
  bool is_in_banner() { return player_cond() & TFCond_Buffed; }
  bool is_bleeding() { return player_cond() & TFCond_Bleeding; }
  bool is_milked() { return player_cond() & TFCond_Milked; }
  bool is_slowed() { return player_cond() & TFCond_Slowed; }
  bool bullet_res() { return player_cond_ex() & TFCondEx_BulletResistance; }
  bool bullet_uber() { return player_cond_ex() & TFCondEx_BulletCharge; }
  bool blast_res() { return player_cond_ex() & TFCondEx_ExplosiveResistance; }
  bool blast_uber() { return player_cond_ex() & TFCondEx_ExplosiveCharge; }
  bool fire_res() { return player_cond_ex() & TFCondEx_FireResistance; }
  bool fire_uber() { return player_cond_ex() & TFCondEx_FireCharge; }

  int  max_health() { return memory::find_vfunc<int(__thiscall*)(void*)>(this, 107)(this); }
  void update_visibility() { memory::find_vfunc<void(__thiscall*)(void*)>(this, 91u)(this); }
  void update_wearables() { memory::find_vfunc<void(__thiscall*)(void*)>(this, 294)(this); }

  // TODO: move the below to the source file
  bool setup_bones(matrix3x4* out, int max, int mask, float time) {
    const auto renderable = this->get_client_renderable();
    return memory::find_vfunc<bool(__thiscall*)(void*, matrix3x4*, int, int, float)>(renderable, 16)(
        renderable, out, max, mask, time);
  }

  vec3 get_hitbox_position(const int hitbox, const vec3 offset = {});
  int get_num_of_hitboxes();

  vec3 get_world_space_center() {
    auto out = origin();
    out.z += (mins().z + maxs().z) * 0.5f;
    return out;
  }

  c_weapon* get_active_weapon();

  vec3 get_shoot_position() { return origin() + view_offset(); }
};

class c_weapon : public c_entity {
public:
  int get_weapon_id() { return memory::find_vfunc<int(__thiscall*)(void*)>(this, 381u)(this); }
};

// TODO: move this to it's own header file
class c_sentry : public c_entity {
public:
  netvar(ammo_shells, int, "DT_ObjectSentrygun", "m_iAmmoShells");
  netvar(ammo_rockets, int, "DT_ObjectSentrygun", "m_iAmmoRockets");
  netvar(state, int, "DT_ObjectSentrygun", "m_iState");
  netvar(is_controlled_by_player, c_base_handle, "DT_ObjectSentrygun", "m_bPlayerControlled");
  netvar(shield_level, int, "DT_ObjectSentrygun", "m_nShieldLevel");
  netvar(is_shielded, bool, "DT_ObjectSentrygun", "m_bShielded");
  netvar(enemy, c_base_handle, "DT_ObjectSentrygun", "m_hEnemy");
  netvar(autoaim_target, c_base_handle, "DT_ObjectSentrygun", "m_hAutoAimTarget");
  netvar(kills, int, "DT_ObjectSentrygun", "m_iKills");
  netvar(assists, int, "DT_ObjectSentrygun", "m_iAssists");
  netvar(health, int, "DT_ObjectSentrygun", "m_iHealth");

  int max_ammo_shells() {
    if ((upgrade_level() == 1) || is_mini_building())
      return SENTRYGUN_MAX_SHELLS_1;
    else
      return SENTRYGUN_MAX_SHELLS_3; // both 2 and 3 are 200
  }

  void get_ammo_count(int& shells, int& max_shells, int& rockets, int& max_rockets) {
    const bool is_mini = is_mini_building();

    shells = ammo_shells();
    max_shells = max_ammo_shells();
    rockets = is_mini ? 0 : ammo_rockets();
    max_rockets = (is_mini || (upgrade_level() < 3)) ? 0 : SENTRYGUN_MAX_ROCKETS;
  }
};

class c_dispenser : public c_entity {
public:
  netvar(health, int, "DT_ObjectDispenser", "m_iHealth");
  netvar(state, int, "DT_ObjectDispenser", "m_iState");
  netvar(ammo_metal, int, "DT_ObjectDispenser", "m_iAmmoMetal");

  int max_metal() { return is_mini_building() ? MINI_DISPENSER_MAX_METAL : DISPENSER_MAX_METAL_AMMO; }
};

class c_teleporter : public c_entity {
public:
  netvar(health, int, "DT_ObjectTeleporter", "m_iHealth");
  netvar(state, int, "DT_ObjectTeleporter", "m_iState");
  netvar(recharge, float, "DT_ObjectTeleporter", "m_flRechargeTime");
  netvar(cur_charge, float, "DT_ObjectTeleporter", "m_flCurrentRechargeDuration");
  netvar(used, int, "DT_ObjectTeleporter", "m_iTimesUsed");
  netvar(exit_yaw, float, "DT_ObjectTeleporter", "m_flYawToExit");
  netvar(match, bool, "DT_ObjectTeleporter", "m_bMatchBuilding");
};