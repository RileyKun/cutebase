//
// Created by Riley on 4/25/2024.
//

#pragma once

#include "link.hpp"

namespace wndproc {
inline HWND    window;
inline WNDPROC original;
LONG __stdcall wnd_proc(HWND window, UINT message, WPARAM wide_param, LPARAM long_param);

void startup();
void shutdown();
} // namespace wndproc