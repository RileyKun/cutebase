//
// Created by Riley on 4/25/2024.
//

#pragma once

#include "constants.hpp"
#include "memory.hpp"
#include "user_cmd.hpp"

typedef enum {
  DPT_Int = 0,
  DPT_Float,
  DPT_Vector,
  DPT_VectorXY,
  DPT_String,
  DPT_Array,
  DPT_DataTable,
  DPT_NUMSendPropTypes
} SendPropType;

class DVariant {
public:
  DVariant() { m_Type = DPT_Float; }
  DVariant(float val) {
    m_Type = DPT_Float;
    m_Float = val;
  }

  union {
    float       m_Float;
    int         m_Int;
    const char* m_pString;
    void*       m_pData; // For DataTables.
    float       m_Vector[3];
  };
  SendPropType m_Type;
};

class RecvTable;
class RecvProp;
class CRecvProxyData {
public:
  const RecvProp* m_pRecvProp; // The property it's receiving.
  DVariant        m_Value;     // The value given to you to store.
  int             m_iElement;  // Which array element you're getting.
  int             m_ObjectID;  // The object being referred to.
};

class CRecvDecoder;

typedef void (*RecvVarProxyFn)(const CRecvProxyData* pData, void* pStruct, void* pOut);
typedef void (*ArrayLengthRecvProxyFn)(void* pStruct, int objectID, int currentArrayLength);
typedef void (*DataTableRecvVarProxyFn)(const RecvProp* pProp, void** pOut, void* pData, int objectID);

class SendProp;
class CSendTablePrecalc;
class send_table {
public:
  typedef SendProp   PropType;
  SendProp*          Props;
  int                PropsCount;
  const char*        NetTableName;
  CSendTablePrecalc* Precalc;

protected:
  bool Initialized : 1;
  bool HasBeenWritten : 1;
  bool HasPropsEncodedAgainstCurrentTickCount : 1;
};

class RecvProp {
public:
  const char*             m_pVarName;
  SendPropType            m_RecvType;
  int                     m_Flags;
  int                     m_StringBufferSize;
  bool                    m_bInsideArray;

  const void*             m_pExtraData;

  RecvProp*               m_pArrayProp;
  ArrayLengthRecvProxyFn  m_ArrayLengthProxy;

  RecvVarProxyFn          m_ProxyFn;
  DataTableRecvVarProxyFn m_DataTableProxyFn;

  RecvTable*              m_pDataTable;
  int                     m_Offset;

  int                     m_ElementStride;
  int                     m_nElements;

  const char*             m_pParentArrayPropName;
};

class RecvTable {
public:
  typedef RecvProp PropType;

  RecvProp*        m_pProps;
  int              m_nProps;
  CRecvDecoder*    m_pDecoder;
  const char*      m_pNetTableName;

  bool             m_bInitialized;
  bool             m_bInMainList;
};

//-----------------------------------------------------------------------------
// Purpose: This data structure is filled in by the engine when the client .dll requests information about
//  other players that the engine knows about
//-----------------------------------------------------------------------------

// Engine player info, no game related infos here
// If you change this, change the two byteswap defintions:
// cdll_client_int.cpp and cdll_engine_int.cpp
typedef struct player_info_s {
  // scoreboard information
  char name[MAX_PLAYER_NAME_LENGTH];
  // local server user ID, unique while server is running
  int  userID;
  // global unique player identifer
  char guid[SIGNED_GUID_LEN + 1];
  // friends identification number
  u32  friendsID;
  // friends name
  char friendsName[MAX_PLAYER_NAME_LENGTH];
  // true, if player is a bot controlled by game.dll
  bool fakeplayer;
  // true if player is the HLTV proxy
  bool ishltv;
  bool isreplay;
  u32  customFiles[4];
  u8   filesDownloaded;
} player_info_t;

//-----------------------------------------------------------------------------
// Purpose: The engine reports to the client DLL what stage it's entering so the DLL can latch events
//  and make sure that certain operations only happen during the right stages.
// The value for each stage goes up as you move through the frame so you can check ranges of values
//  and if new stages get added in-between, the range is still valid.
//-----------------------------------------------------------------------------
enum frame_stage {
  FRAME_UNDEFINED = -1, // (haven't run any frames yet)
  FRAME_START,
  // A network packet is being received
  FRAME_NET_UPDATE_START,
  // Data has been received and we're going to start calling PostDataUpdate
  FRAME_NET_UPDATE_POSTDATAUPDATE_START,
  // Data has been received and we've called PostDataUpdate on all data recipients
  FRAME_NET_UPDATE_POSTDATAUPDATE_END,
  // We've received all packets, we can now do interpolation, prediction, etc..
  FRAME_NET_UPDATE_END,

  // We're about to start rendering the scene
  FRAME_RENDER_START,
  // We've finished rendering the scene.
  FRAME_RENDER_END
};

typedef void* (*CreateClientClassFn)(int entnum, int serialNum);
typedef void* (*CreateEventFn)();
class client_class {
public:
  CreateClientClassFn m_pCreateFn;
  CreateEventFn       m_pCreateEventFn; // Only called for event objects.
  const char*         m_pNetworkName;
  RecvTable*          m_pRecvTable;
  client_class*       m_pNext;
  int                 m_ClassID; // Managed by the engine.

  e_class_ids         get_class() { return static_cast<e_class_ids>(m_ClassID); }
};

class bf_write;
class c_hl_client {
public:
  client_class* get_all_classes();
  void          create_move(float sample_time, bool active);
  bool          write_cmd_to_buffer(bf_write* buf, int from, int to, bool is_new_cmd);
};

class c_engine_client {
public:
  void             get_screen_size(int& w, int& h);
  void             client_cmd(const char* input);
  void             client_cmd_unrestricted(const char* input);
  bool             get_player_info(int entidx, player_info_t* info);
  int              get_local_player();
  float            plat_float_time();
  void             get_view_angles(QAngle& va);
  void             set_view_angles(QAngle& va);
  int              get_max_clients();
  // is not loading anymore but is connected
  bool             is_in_game();
  // is connected but still loading
  bool             is_connected();
  // returns the game's root directory
  const char*      get_game_directory();
  const matrix4x4& world_to_screen_matrix();
};

class client_mode_shared {
public:
};