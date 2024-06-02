//
// Created by Riley on 4/25/2024.
//

#pragma once

#include "link.hpp"

class c_main_menu {
private:
  enum menu_tabs {
    TAB_AIMBOT = 0,
    TAB_VISUALS,
    TAB_HVH,
    TAB_MISC,
    TAB_CONFIG
  };

  /*enum cur_visuals {
    DROP_ESP = 0,
    DROP_CHAMS,
    DROP_GLOW,
    DROP_MISC
  };*/
  enum cur_visuals {
    DROP_GENERAL = 0,
    DROP_CAMERA,
    DROP_MISC,
  };

  const char* config_combo[3]{"Main", "Camera", "Misc"};

  int tab = 0;
  int visuals_config = 0;

  void start_styles(); // TODO: Pixy; styling
public:
  void draw();
};

namespace ImGui {
  inline void MultiComboBox(std::vector<const char*> titles, const std::vector<bool*>& options,
                            const std::string& label);
  inline bool Hotkey(const char* label, int& k, bool& getting_key, const ImVec2& size_arg = ImVec2(0, 0));
}