//
// Created by Riley on 4/25/2024.
//

#pragma once

#include <d3d9.h>
#include <imgui.h>

#include <format>
#include <memory>
#include <mutex>
#include <variant>
#include <vector>

#include "../typedefs.hpp"

using color = ImColor;

enum class e_text_align : u8 {
  TEXT_LEFT,
  TEXT_CENTER,
  TEXT_RIGHT
};

class c_render {
public:
  void string(ImDrawList* list, ImFont* font, int x, int y, bool outlined, e_text_align align, ImColor col,
              std::string_view input);
  void circle(ImDrawList* list, int x, int y, float rad, bool outlined, ImColor col);
  void box(ImDrawList* list, int x, int y, int w, int h, bool outlined, ImColor col);
  void filled_box(ImDrawList* list, int x, int y, int w, int h, ImColor col);
  void line(ImDrawList* list, int x1, int y1, int x2, int y2, ImColor col);

  template <class... Args>
  void string(ImDrawList* list, ImFont* font, int x, int y, bool outlined, e_text_align align, ImColor col,
              std::string_view input, Args&&... args) {
    string(list, font, x, y, outlined, align, col, std::vformat(input, std::make_format_args(args...)));
  }
};

class c_render_threaded {
public:
  c_render_threaded() = default;

  void string(ImFont* font, int x, int y, bool outlined, e_text_align align, ImColor col,
              const std::string& input);
  void circle(int x, int y, float rad, bool outlined, ImColor col);
  void box(int x, int y, int width, int height, bool outlined, ImColor col);
  void filled_box(int x, int y, int width, int height, ImColor col);
  void line(int x1, int y1, int x2, int y2, ImColor col);

  template <class... Args>
  void string(ImFont* font, int x, int y, bool outlined, e_text_align align, ImColor col, std::string& input,
              Args&&... args) {
    string(font, x, y, outlined, align, col, std::vformat(input, std::make_format_args(args...)));
  }

  // send commands
  void flush();

  // traverse paint commands to our hook
  void paint_traverse(ImDrawList* list);

private:
  struct string_t {
    ImFont*      font{};
    int          x{};
    int          y{};
    bool         outlined{};
    e_text_align align{};
    ImColor      col{};
    std::string  input{};
  };

  struct box_t {
    int     x{};
    int     y{};
    int     width{};
    int     height{};
    bool    outlined{};
    ImColor col{};
  };

  struct filled_box_t {
    int     x{};
    int     y{};
    int     width{};
    int     height{};
    ImColor col{};
  };

  struct line_t {
    int     x1{};
    int     x2{};
    int     y1{};
    int     y2{};
    ImColor col{};
  };

  struct circle_t {
    int     x{};
    int     y{};
    float   rad{};
    bool    outlined{};
    ImColor col{};
  };

  // lol wtf is clang-format
  std::mutex                                                                 m_mutex{};
  std::vector<std::variant<string_t, box_t, filled_box_t, circle_t, line_t>> m_cmds{}, m_safe_cmds{};
};

class c_drawsystem {
public:
  void initialize(IDirect3DDevice9* device, HWND window);
  void start_paint(IDirect3DDevice9* device);
  void finish_paint(IDirect3DDevice9* device);

private:
  DWORD m_prev_srgb{};
};

namespace fonts {
inline ImFont* FONT_SEGOE;
} // namespace fonts