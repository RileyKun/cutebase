//
// Created by Riley on 4/28/2024.
//

#pragma once

#include "clc_move.hpp"
#include "md5.hpp"
#include "utlvector.hpp"

#include "cdll_int.hpp"

class CSaveRestoreData;

//-----------------------------------------------------------------------------
// Purpose: Global variables used by shared code
//-----------------------------------------------------------------------------
class c_global_vars_base {
public:
  // Absolute time (per frame still - Use Plat_FloatTime() for a high precision real time
  //  perf clock, but not that it doesn't obey host_timescale/host_framerate)
  float             realtime;
  // Absolute frame counter
  int               framecount;
  // Non-paused frametime
  float             absoluteframetime;
  // Current time
  //
  // On the client, this (along with tickcount) takes a different meaning based on what
  // piece of code you're in:
  //
  //   - While receiving network packets (like in PreDataUpdate/PostDataUpdate and proxies),
  //     this is set to the SERVER TICKCOUNT for that packet. There is no interval between
  //     the server ticks.
  //     [server_current_Tick * tick_interval]
  //
  //   - While rendering, this is the exact client clock
  //     [client_current_tick * tick_interval + interpolation_amount]
  //
  //   - During prediction, this is based on the client's current tick:
  //     [client_current_tick * tick_interval]
  float             cur_time;
  // Time spent on last server or client frame (has nothing to do with think intervals)
  float             frame_time;
  // current maxplayers setting
  int               max_clients;
  // Simulation ticks
  int               tick_count;
  // Simulation tick interval
  float             interval_per_tick;
  // interpolation amount ( client-only ) based on fraction of next tick which has elapsed
  float             interpolation_amount;
  int               sim_ticks_this_frame;
  int               network_protocol;
  // current saverestore data
  CSaveRestoreData* save_data;

public:
  // Set to true in client code.
  bool is_client;
  // 100 (i.e., tickcount is rounded down to this base and then the "delta" from this base is networked
  int  time_stamp_networking_base;
  // 32 (entindex() % nTimestampRandomizeWindow ) is subtracted from gpGlobals->tickcount to set the
  // networking basis, prevents
  //  all of the entities from forcing a new PackedEntity on the same tick (i.e., prevents them from getting
  //  lockstepped on this)
  int  time_stamp_randomize_window;
};

enum {
  // This controls how much it smoothes out the samples from the server.
  NUM_CLOCKDRIFT_SAMPLES = 16
};

class c_clock_drift_manager {
public:
  // This holds how many ticks the client is ahead each time we get a server tick.
  // We average these together to get our estimate of how far ahead we are.
  float clock_offsets[NUM_CLOCKDRIFT_SAMPLES];
  int   cur_clock_offset;

  int   server_tick; // Last-received tick from the server.
  int   client_tick; // The client's own tick counter (specifically, for interpolation during rendering).
                     // The server may be on a slightly different tick and the client will drift towards it.
};

struct AddAngle {
  float total;
  float starttime;
};

class CEventInfo
{
public:
  enum
  {
    EVENT_INDEX_BITS = 8,
    EVENT_DATA_LEN_BITS = 11,
    MAX_EVENT_DATA = 192,  // ( 1<<8 bits == 256, but only using 192 below )
  };

  ~CEventInfo( )
  {
    if ( pData )
    {
      delete pData;
    }
  }

  // 0 implies not in use
  short classID;

  // If non-zero, the delay time when the event should be fired ( fixed up on the client )
  float fire_delay;

  // send table pointer or NULL if send as full update
  const send_table* pSendTable;
  const client_class* pClientClass;

  // Length of data bits
  int		bits;
  // Raw event data
  byte* pData;
  // CLIENT ONLY Reliable or not, etc.
  int		flags;
private:
  char pad[ 24 ];
public:
  CEventInfo* next;
};

// a client can have up to 4 customization files (logo, sounds, models, txt).
#define MAX_CUSTOM_FILES            4 // max 4 files
#define MAX_AREA_STATE_BYTES        32
#define MAX_AREA_PORTAL_STATE_BYTES 24

typedef unsigned int CRC32_t;
typedef struct CustomFile_s {
  CRC32_t      crc;   // file CRC
  unsigned int reqID; // download request ID
} CustomFile_t;

class c_client_state {
public:
private:
  char pad_0000[8]; // 0x0000
public:
  void* thisptr = nullptr; // 0x0008
private:
  char pad_000C[4]; // 0x000C
public:
  CNetChannel* m_NetChannel = nullptr; // 0x0010
private:
  char pad_0014[316]; // 0x0014
public:
  int                   m_nCurrentSequence = 0; // 0x0150
  c_clock_drift_manager m_ClockDriftMgr = {};   // 0x0154
  int                   m_nDeltaTick = 0;       // 0x01A0
private:
  char pad_01A4[16]; // 0x01A4
public:
  char m_szLevelFileName[128]; // 0x01B4
  char m_szLevelBaseName[128]; // 0x0234
  int  m_nMaxClients = 0;      // 0x02B4
private:
  char pad_02B8[18528]; // 0x02B8
public:
  int                  oldtickcount = 0;        // 0x4B18
  float                m_tickRemainder = 0.f;   // 0x4B1C
  float                m_frameTime = 0.f;       // 0x4B20
  int                  lastoutgoingcommand = 0; // 0x4B24
  int                  chokedcommands = 0;      // 0x4B28
  int                  last_command_ack = 0;    // 0x4B2C
  int                  command_ack = 0;         // 0x4B30
  int                  m_nSoundSequence = 0;
  bool                 ishltv;
  MD5Value_t           serverMD5;
  unsigned char        m_chAreaBits[MAX_AREA_STATE_BYTES];
  unsigned char        m_chAreaPortalBits[MAX_AREA_PORTAL_STATE_BYTES];
  bool                 m_bAreaBitsValid;
  QAngle               viewangles;
  CUtlVector<AddAngle> addangle;
  float                addangletotal;
  float                prevaddangletotal;
  int                  cdtrack;
  CustomFile_t         m_nCustomFiles[MAX_CUSTOM_FILES];
  unsigned int         m_nFriendsID;
  char                 m_FriendsName[MAX_PLAYER_NAME_LENGTH];
  CEventInfo*          events;
};