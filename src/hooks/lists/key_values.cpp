//
// Created by Riley on 4/29/2024.
//

#include "../hooks.hpp"

#include <safetyhook.hpp>

SafetyHookInline kv{}, is_dom{};

// 8B 4D ? 56 57 8B 01 FF 90 ? ? ? ? 6A
// 8B 0D ? ? ? ? 81 C1 50 05 00 00 57 8B 01 8B 40 10 FF D0 84 C0 0F 84 FD 00 00 00

// E8 ? ? ? ? 84 C0 74 22 8B 45 FC

namespace s {
auto desired = memory::find_pattern<DWORD, 5u>("client.dll", "E8 ? ? ? ? 8B 4D FC 56 57");
auto is_dom_desired = memory::find_pattern<DWORD, 5u>("client.dll", "E8 ? ? ? ? 84 C0 74 22 8B 45 FC");
auto jump = memory::find_pattern<DWORD>(
    "client.dll", "8B 0D ? ? ? ? 81 C1 50 05 00 00 57 8B 01 8B 40 10 FF D0 84 C0 0F 84 FD 00 00 00");
} // namespace s

void vf hooks::key_values::set_int(registers, const char* name, int val) {

  kv.thiscall<void>(ecx, name, val);

  if ((DWORD)_ReturnAddress() == s::desired && !strcmp(name, "nemesis"))
    *static_cast<uptr*>(_AddressOfReturnAddress()) = s::jump;
}

void hooks::key_values::startup() {
  is_dom = safetyhook::create_inline(
      memory::find_pattern<DWORD>("client.dll", "55 8B EC 56 57 8B F1 E8 ? ? ? ? 8B F8 85 FF 75 08"),
      is_player_dominated);
  kv = safetyhook::create_inline(
      memory::find_pattern<DWORD>(
          "client.dll",
          "55 8B EC 6A ? FF 75 ? E8 ? ? ? ? 85 C0 74 ? 8B 4D ? 89 48 ? C6 40 ? ? 5D C2 ? ? CC 55 8B EC 56"),
      set_int);
}

void hooks::key_values::shutdown() {
  kv = {};
  is_dom = {};
}

bool vf hooks::key_values::is_player_dominated(void* ecx, void* edx, int index) {
  auto result = is_dom.thiscall<bool>(ecx, index);

  if (!result) {
    if ((DWORD)_ReturnAddress() == s::is_dom_desired)
      *reinterpret_cast<DWORD*>(_AddressOfReturnAddress()) = s::jump;
  }

  return result;
}
