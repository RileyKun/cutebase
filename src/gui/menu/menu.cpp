//
// Created by Riley on 4/25/2024.
//

#include "menu.hpp"
#include "link.hpp"

void c_main_menu::draw() {
  using namespace ImGui;

  // 548, 450
  SetNextWindowSize({548, 450}, ImGuiCond_Once);
  SetNextWindowPos({(float)ctx->screen_width / 2 - 274, (float)ctx->screen_height / 2 - 225}, ImGuiCond_Once);

  Begin("cutebase", nullptr,
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);
  {
    // write your menu code here
  }

  End();
}

// definitely didn't paste this
void ImGui::MultiComboBox(std::vector<const char*> titles, const std::vector<bool*>& options,
                          const std::string& label) {
  if (titles.size() != options.size())
    return;

  std::string preview = "<None>##";
  for (size_t i = 0; i < options.size(); i++) {
    if (*options[i]) {
      if (preview == "<None>##") {
        preview = "";
      }
      preview += titles[i];
      preview.append(", ");
    }
  }
  preview.pop_back();
  preview.pop_back();

  if (BeginCombo(label.c_str(), preview.c_str())) {
    for (size_t i = 0; i < titles.size(); i++) {
      Selectable((*options[i]) ? std::format("+ {}", titles[i]).c_str() : titles[i], options[i],
                 ImGuiSelectableFlags_DontClosePopups);
    }
    EndCombo();
  }
}

static const char* KeyNames[] = {"OFF",
                                 "M1",
                                 "M2",
                                 "VK_CANCEL",
                                 "M3",
                                 "M4",
                                 "M5",
                                 "UNK",
                                 "BKSPC",
                                 "TAB",
                                 "Unknown",
                                 "Unknown",
                                 "VK_CLEAR",
                                 "ENTER",
                                 "Unknown",
                                 "Unknown",
                                 "SHIFT",
                                 "CTRL",
                                 "ALT",
                                 "PAUSE",
                                 "CAPS",
                                 "VK_KANA",
                                 "Unknown",
                                 "VK_JUNJA",
                                 "VK_FINAL",
                                 "VK_KANJI",
                                 "Unknown",
                                 "ESC",
                                 "VK_CONVERT",
                                 "VK_NONCONVERT",
                                 "VK_ACCEPT",
                                 "VK_MODECHANGE",
                                 "SPC",
                                 "PGUP",
                                 "PGDN",
                                 "END",
                                 "HOME",
                                 "LEFT",
                                 "UP",
                                 "RIGHT",
                                 "DOWN",
                                 "SEL",
                                 "PRNT",
                                 "VK_EXECUTE",
                                 "PTSC",
                                 "INS",
                                 "DEL",
                                 "VK_HELP",
                                 "0",
                                 "1",
                                 "2",
                                 "3",
                                 "4",
                                 "5",
                                 "6",
                                 "7",
                                 "8",
                                 "9",
                                 "Unknown",
                                 "Unknown",
                                 "Unknown",
                                 "Unknown",
                                 "Unknown",
                                 "Unknown",
                                 "Unknown",
                                 "A",
                                 "B",
                                 "C",
                                 "D",
                                 "E",
                                 "F",
                                 "G",
                                 "H",
                                 "I",
                                 "J",
                                 "K",
                                 "L",
                                 "M",
                                 "N",
                                 "O",
                                 "P",
                                 "Q",
                                 "R",
                                 "S",
                                 "T",
                                 "U",
                                 "V",
                                 "W",
                                 "X",
                                 "Y",
                                 "Z",
                                 "VK_LWIN",
                                 "VK_RWIN",
                                 "VK_APPS",
                                 "Unknown",
                                 "VK_SLEEP",
                                 "NUM0",
                                 "NUM1",
                                 "NUM2",
                                 "NUM3",
                                 "NUM4",
                                 "NUM5",
                                 "NUM6",
                                 "NUM7",
                                 "NUM8",
                                 "NUM9",
                                 "MULT",
                                 "ADD",
                                 "SEP",
                                 "SUB",
                                 "DECIMAL",
                                 "DIVIDE",
                                 "F1",
                                 "F2",
                                 "F3",
                                 "F4",
                                 "F5",
                                 "F6",
                                 "F7",
                                 "F8",
                                 "F9",
                                 "F10",
                                 "F11",
                                 "F12",
                                 "F13",
                                 "F14",
                                 "F15",
                                 "F16",
                                 "F17",
                                 "F18",
                                 "F19",
                                 "F20",
                                 "F21",
                                 "F22",
                                 "F23",
                                 "F24",
                                 "Unknown",
                                 "Unknown",
                                 "Unknown",
                                 "Unknown",
                                 "Unknown",
                                 "Unknown",
                                 "Unknown",
                                 "Unknown",
                                 "NUMLOCK",
                                 "SCRLOCK",
                                 "VK_OEM_NEC_EQUAL",
                                 "VK_OEM_FJ_MASSHOU",
                                 "VK_OEM_FJ_TOUROKU",
                                 "VK_OEM_FJ_LOYA",
                                 "VK_OEM_FJ_ROYA",
                                 "Unknown",
                                 "Unknown",
                                 "Unknown",
                                 "Unknown",
                                 "Unknown",
                                 "Unknown",
                                 "Unknown",
                                 "Unknown",
                                 "Unknown",
                                 "SHIFT",
                                 "SHIFT",
                                 "CTRL",
                                 "CTRL",
                                 "ALT",
                                 "ALT"};

// TODO: for the love of god someone redo this please
bool               ImGui::Hotkey(const char* label, int& k, bool& getting_key, const ImVec2& size_arg) {
  static std::string sz_text("NONE");

  if (ImGui::Button(sz_text.c_str(), size_arg))
    getting_key = true;

  if (getting_key) {
    for (auto i = 1; i < 256; i++) {
      if (GetAsyncKeyState(i) & 0x8000) {
        if (i != 12) {
          k = (i == VK_ESCAPE) ? 0 : i;
          getting_key = false;
        }
      }
    }
    sz_text = "...";
  } else if (!getting_key && k == 0)
    sz_text = "NONE";
  else if (!getting_key && k != 0)
    sz_text = std::string(KeyNames[k]);

  return false;
}