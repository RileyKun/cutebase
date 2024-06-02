//
// Created by Riley on 4/25/2024.
//

#include "../wndproc.hpp"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam,
                                                             LPARAM lParam);

LONG __stdcall wndproc::wnd_proc(HWND window, UINT message, WPARAM wide_param, LPARAM long_param) {
  if (ctx->menu_open) {
    ImGui_ImplWin32_WndProcHandler(window, message, wide_param, long_param);

    if (ImGui::GetIO().WantTextInput) {
      g_tf2.input_system->reset_input_state();
      return 1;
    }
    if (message >= WM_MOUSEFIRST && WM_MOUSELAST >= message)
      return 1;
  }
  return CallWindowProc(original, window, message, wide_param, long_param);
}

void wndproc::startup() {
  while (!window)
    window = FindWindowA("Valve001", nullptr); // big boss says don't find tf2 directly

  original = (WNDPROC)(SetWindowLongPtr(window, GWL_WNDPROC, (LONG_PTR)wnd_proc));
}

void wndproc::shutdown() {
  SetWindowLongPtr(window, GWL_WNDPROC, (LONG_PTR)original);
}