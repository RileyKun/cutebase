//
// Created by Riley on 4/24/2024.
//

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_aligned.hpp>

typedef char               i8;
typedef short              i16;
typedef int                i32;
typedef long long          i64;

typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;

typedef unsigned long      DWORD;

#if __x86_64__
typedef u64 uptr;
#else
typedef u32 uptr;
#endif // __x86_64__

typedef void* (*cint_fn)(const char* name, int* return_code);

#define registers void *ecx, void *edx

#define api       __stdcall
#define vf        __fastcall

using QAngle = glm::vec3;
using Vector = glm::vec3;
using matrix3x4 = glm::mat3x4;
using matrix4x4 = glm::mat4x4;
using vec3 = glm::vec3;
using vec2 = glm::vec2;
using VectorAligned = glm::aligned_vec3;

#include <Windows.h>
#include <memory>

#define singleton(name, target_class) \
  inline auto name = std::make_unique<target_class>();

#define singleton_feature(name, target_class) \
  namespace f { inline target_class name; }