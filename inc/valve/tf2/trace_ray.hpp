//
// Created by Riley on 4/27/2024.
//

#pragma once

#include "constants.hpp"
#include "memory.hpp"

// plane_t structure
// !!! if this is changed, it must be changed in asm code too !!!
// FIXME: does the asm code even exist anymore?
struct cplane_t {
  Vector normal;
  float  dist;
  byte   type;     // for fast side tests
  byte   signbits; // signx + (signy<<1) + (signz<<1)
  byte   pad[2];
};

//-----------------------------------------------------------------------------
// A ray...
//-----------------------------------------------------------------------------

struct ray_t {
  VectorAligned m_Start;       // starting point, centered within the extents
  VectorAligned m_Delta;       // direction + length of the ray
  VectorAligned m_StartOffset; // Add this to m_Start to get the actual ray start
  VectorAligned m_Extents;     // Describes an axis aligned box extruded along a ray
  bool          m_IsRay;       // are the extents zero?
  bool          m_IsSwept;     // is delta != 0?

  void          init(const Vector& start, const Vector& end) {
    m_Delta = end - start;
    m_IsSwept = (glm::length(m_Delta) != 0);
    m_Extents = {};
    m_IsRay = true;
    m_StartOffset = {};
    m_Start = start;
  }

  void init(const Vector& start, const Vector& end, const Vector& mins, const Vector& maxs) {
    m_Delta = end - start;
    m_IsSwept = (glm::length(m_Delta) != 0);
    m_Extents = maxs - mins;
    m_Extents *= 0.5f;
    m_IsRay = (glm::length(m_Extents) < 1e-6);
    m_StartOffset = mins + maxs;
    m_StartOffset *= 0.5f;
    {
      // fuck glm
      auto start_temp = (Vector)m_StartOffset;
      m_Start = start + start_temp;
    }
    m_StartOffset *= -1.0f;
  }

  Vector InvDelta() const {
    Vector vecInvDelta;

    for (int iAxis = 0; iAxis < 3; ++iAxis) {
      if (m_Delta[iAxis] != 0.0f)
        vecInvDelta[iAxis] = 1.0f / m_Delta[iAxis];

      else
        vecInvDelta[iAxis] = FLT_MAX;
    }

    return vecInvDelta;
  }
};

//=============================================================================
// Base Trace Structure
// - shared between engine/game dlls and tools (vrad)
//=============================================================================

class c_base_trace {
public:
  // Displacement flags tests.
  bool           IsDispSurface(void) { return ((dispFlags & DISPSURF_FLAG_SURFACE) != 0); }
  bool           IsDispSurfaceWalkable(void) { return ((dispFlags & DISPSURF_FLAG_WALKABLE) != 0); }
  bool           IsDispSurfaceBuildable(void) { return ((dispFlags & DISPSURF_FLAG_BUILDABLE) != 0); }
  bool           IsDispSurfaceProp1(void) { return ((dispFlags & DISPSURF_FLAG_SURFPROP1) != 0); }
  bool           IsDispSurfaceProp2(void) { return ((dispFlags & DISPSURF_FLAG_SURFPROP2) != 0); }

  // these members are aligned!!
  Vector         startpos; // start position
  Vector         endpos;   // final position
  cplane_t       plane;    // surface normal at impact

  float          fraction; // time completed, 1.0 = didn't hit anything

  int            contents;  // contents on other side of surface hit
  unsigned short dispFlags; // displacement flags for marking surfaces with data

  bool           allsolid;   // if true, plane is not valid
  bool           startsolid; // if true, the initial point was in a solid area

  c_base_trace() {}
};

struct surface_t {
  const char*    name;
  short          surfaceProps;
  unsigned short flags;      // BUGBUG: These are declared per surface, not per material, but this database is
                             // per-material now
  bool           allsolid;   // if true, plane is not valid
  bool           startsolid; // if true, the initial point was in a solid area
};

class c_entity;
class i_client_entity;
class c_base_trace;

//-----------------------------------------------------------------------------
// Purpose: A trace is returned when a box is swept through the world
// NOTE: eventually more of this class should be moved up into the base class!!
//-----------------------------------------------------------------------------
class c_game_trace : public c_base_trace {
public:
  // Returns true if hEnt points at the world entity.
  // If this returns true, then you can't use GetHitBoxIndex().
  bool      did_hit_world() const { return ent == nullptr; }

  // Returns true if we hit something and it wasn't the world.
  bool      did_hit_non_world_entity() const { return ent != nullptr && !did_hit_world(); }

  // Gets the entity's network index if the trace has hit an entity.
  // If not, returns -1.
  // WARNING: NOT AN ACTUAL FUNCTION
  int       get_entity_index() const { return 0; }

  // Returns true if there was any kind of impact at all
  bool      did_hit() const { return fraction < 1 || allsolid || startsolid; }

  float     fractionleftsolid; // time we left a solid, only valid if we started in solid
  surface_t surface;           // surface hit (impact surface)

  int       hitgroup;    // 0 == generic, non-zero is specific body part
  short     physicsbone; // physics bone hit by trace in studio

  c_entity* ent;
  int       hitbox;
};

//-----------------------------------------------------------------------------
// The standard trace filter... NOTE: Most normal traces inherit from CTraceFilter!!!
//-----------------------------------------------------------------------------
enum trace_type {
  TRACE_EVERYTHING = 0,
  TRACE_WORLD_ONLY,              // NOTE: This does *not* test static props!!!
  TRACE_ENTITIES_ONLY,           // NOTE: This version will *not* test static props
  TRACE_EVERYTHING_FILTER_PROPS, // NOTE: This version will pass the IHandleEntity for props through the
                                 // filter, unlike all other filters
};

class i_trace_filter {
public:
  virtual bool       should_hit_entity(void* pEntity, int contentsMask) = 0;
  virtual trace_type get_trace_type() const = 0;
};

//-----------------------------------------------------------------------------
// Classes are expected to inherit these + implement the ShouldHitEntity method
//-----------------------------------------------------------------------------

// This is the one most normal traces will inherit from
class c_trace_filter : public i_trace_filter {
public:
  virtual trace_type get_trace_type() const { return TRACE_EVERYTHING; }
};

class c_trace_filter_entities_only : public i_trace_filter {
public:
  virtual trace_type get_trace_type() const { return TRACE_ENTITIES_ONLY; }
};

//-----------------------------------------------------------------------------
// Classes need not inherit from these
//-----------------------------------------------------------------------------
class c_trace_filter_world_only : public i_trace_filter {
public:
  bool               should_hit_entity(void* pServerEntity, int contentsMask) { return false; }
  virtual trace_type get_trace_type() const { return TRACE_WORLD_ONLY; }
};

class c_trace_filter_world_and_props_only : public i_trace_filter {
public:
  bool               should_hit_entity(void* pServerEntity, int contentsMask) { return false; }
  virtual trace_type get_trace_type() const { return TRACE_EVERYTHING; }
};

class c_trace_filter_hit_all : public c_trace_filter {
public:
  virtual bool should_hit_entity(void* pServerEntity, int contentsMask) { return true; }
};

class c_trace_filter_hitscan : public c_trace_filter {
public:
  bool       should_hit_entity(void* ent, int contents) override { return true; }

  virtual trace_type get_trace_type() const override { return TRACE_EVERYTHING; }

  i_client_entity*   skip = nullptr;
};

class i_engine_trace {
public:
  // A version that simply accepts a ray (can work as a traceline or tracehull)
  void trace_ray(const ray_t& ray, unsigned int mask, i_trace_filter* filter, c_game_trace* trace) {
    memory::find_vfunc<void(__thiscall*)(void*, const ray_t&, unsigned int, i_trace_filter*, c_game_trace*)>(
        this, 4u)(this, ray, mask, filter, trace);
  }
}; 