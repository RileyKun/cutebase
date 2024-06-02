//
// Created by Riley on 4/24/2024.
//

#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DISABLE_OBSOLETE_KEYIO

#include "../hooks/hooks.hpp"

class c_factory {
public:
  void startup();
  void shutdown();

  bool should_unload();

  int dx_level = 0;

  bool failed = false;
};

singleton(factory, c_factory);
singleton(g_hooks, c_hook_manager);