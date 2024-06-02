//
// Created by Riley on 5/9/2024.
//

#pragma once

#include "memory.hpp"

class c_game_event {
public:
  virtual ~c_game_event();
  const char* get_name() const;
  bool        is_empty(const char* keyName = NULL);
  bool        is_local() const;
  bool        is_reliable() const;
  bool        get_bool(const char* keyName = NULL, bool defaultValue = false);
  int         get_int(const char* keyName = NULL, int defaultValue = 0);
  float       get_float(const char* keyName = NULL, float defaultValue = 0.0f);
  const char* get_string(const char* keyName = NULL, const char* defaultValue = "");
  void        set_bool(const char* keyName, bool value);
  void        set_bnt(const char* keyName, int value);
  void        set_float(const char* keyName, float value);
  void        set_string(const char* keyName, const char* value);
};

// A safer method than inheriting straight from IGameEventListener2.
// Avoids requiring the user to remove themselves as listeners in
// their destructor, and sets the serverside variable based on
// our dll location.
class c_game_event_listener {
public:
  virtual ~c_game_event_listener() {}

  // Intentionally abstract
  virtual void fire_game_event(c_game_event* event) = 0;
  virtual int  get_event_debug_id() { return m_debug; }

private:
  // Have we registered for any events?
  int m_debug;
};

class CSVCMsg_GameEvent;
class c_game_event_manager {
public: // IGameEventManager functions
  virtual ~c_game_event_manager();
  virtual int   load_events_from_file(const char* filename) = 0;
  virtual void  reset() = 0;
  virtual bool  add_listener(c_game_event_listener* listener, const char* name, bool bServerSide) = 0;
  virtual bool  find_listener(c_game_event_listener* listener, const char* name) = 0;
  virtual void  remove_listener(c_game_event_listener* listener) = 0;
  virtual void  add_listener_global(c_game_event_listener* listener, bool server_side) = 0;
  c_game_event* create_new_event(const char* name, bool force = false) {
    return memory::find_vfunc<c_game_event*(__thiscall*)(void*, const char*, bool)>(this, 6u)(this, name,
                                                                                              force);
  }
  virtual bool          fire_event(c_game_event* pEvent, bool bDontBroadcast = false) = 0;
  virtual bool          fire_event_client_side(c_game_event* pEvent) = 0;
  virtual c_game_event* duplicate_event(c_game_event* pEvent) = 0;
  virtual void          free_event(c_game_event* pEvent) = 0;
  virtual bool          serialize_event(c_game_event* pEvent, CSVCMsg_GameEvent* pEventMsg) = 0;
  virtual c_game_event* unserialize_event(const CSVCMsg_GameEvent& eventMsg) = 0;
  virtual void*         get_event_data_types(c_game_event* pEvent) = 0;
};