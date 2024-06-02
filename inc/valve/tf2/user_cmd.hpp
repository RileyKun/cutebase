//
// Created by Riley on 4/25/2024.
//

#pragma once

#include "typedefs.hpp"

class c_user_cmd {
public:
  virtual ~c_user_cmd(){};

  // For matching server and client commands for debugging
  int    command_number;

  // the tick the client created this command
  int    tick_count;

  // Player instantaneous view angles.
  QAngle viewangles;
  // Intended velocities
  //	forward velocity.
  float  forwardmove;
  //  sideways velocity.
  float  sidemove;
  //  upward velocity.
  float  upmove;
  // Attack button states
  int    buttons;
  // Impulse command issued.
  byte   impulse;
  // Current weapon id
  int    weaponselect;
  int    weaponsubtype;

  int    random_seed; // For shared random functions

  short  mousedx; // mouse accum in x from create move
  short  mousedy; // mouse accum in y from create move

  // Client only, tracks whether we've predicted this command at least once
  bool   hasbeenpredicted;
};