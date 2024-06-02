//
// Created by Riley on 4/27/2024.
//

#pragma once

#include "typedefs.hpp"
#include <string_view>

struct studiohwdata_t;
struct color_mesh_info_t;
using studio_decal_handle = void*;

constexpr std::string_view TEXTURE_GROUP_OTHER = "Other textures";

enum light_type {
  MATERIAL_LIGHT_DISABLE = 0,
  MATERIAL_LIGHT_POINT,
  MATERIAL_LIGHT_DIRECTIONAL,
  MATERIAL_LIGHT_SPOT,
};

// intersection boxes
struct mstudiobbox_t {
  int         bone;
  int         group; // intersection group
  Vector      bbmin; // bounding box
  Vector      bbmax;
  int         szhitboxnameindex; // offset to the name of the hitbox.
  int         unused[8];
  const char* pszHitboxName() {
    if (szhitboxnameindex == 0)
      return "";

    return ((const char*)this) + szhitboxnameindex;
  }
  mstudiobbox_t() {}

private:
  // No copy constructors allowed
  mstudiobbox_t(const mstudiobbox_t& vOther);
};

struct mstudiohitboxset_t {
  int                   sznameindex;
  inline char* const    pszName(void) const { return ((char*)this) + sznameindex; }
  int                   numhitboxes;
  int                   hitboxindex;
  inline mstudiobbox_t* pHitbox(int i) const { return (mstudiobbox_t*)(((byte*)this) + hitboxindex) + i; };
};

struct mstudiobone_t {
  int                sznameindex;
  inline char* const pszName(void) const { return ((char*)this) + sznameindex; }
  int                parent;            // parent bone
  int                bonecontroller[6]; // bone controller index, -1 == none
  // default values
  Vector             pos;
  void*              quat;
  void*              rot;
  // compression scale
  Vector             posscale;
  Vector             rotscale;
  matrix3x4          poseToBone;
  void*              qAlignment;
  int                flags;
  int                proctype;
  int                procindex;   // procedural rule
  mutable int        physicsbone; // index into physically simulated bone
  inline void*       pProcedure() const {
    if (procindex == 0)
      return NULL;
    else
      return (void*)(((byte*)this) + procindex);
  };
  int                surfacepropidx; // index into string tablefor property name
  inline char* const pszSurfaceProp(void) const { return ((char*)this) + surfacepropidx; }
  int                contents;  // See BSPFlags.h for the contents flags
  int                unused[8]; // remove as appropriate

  mstudiobone_t() {}

private:
  mstudiobone_t(const mstudiobone_t& other);
};
struct studiohdr_t {
  int                   id;
  int                   version;
  int                   checksum; // this has to be the same in the phy and vtx files to load!
  char                  name[64];
  int                   length;
  Vector                eyeposition;   // ideal eye position
  Vector                illumposition; // illumination center
  Vector                hull_min;      // ideal movement hull size
  Vector                hull_max;
  Vector                view_bbmin; // clipping bounding box
  Vector                view_bbmax;
  int                   flags;
  int                   numbones; // bones
  int                   boneindex;
  inline mstudiobone_t* get_bone(int i) const { return (mstudiobone_t*)(((byte*)this) + boneindex) + i; };
  int                   numbonecontrollers; // bone controllers
  int                   bonecontrollerindex;
  int                   numhitboxsets;
  int                   hitboxsetindex;
  inline mstudiohitboxset_t* get_hitbox_set(int i) const {
    return (mstudiohitboxset_t*)(((byte*)this) + hitboxsetindex) + i;
  }
  inline mstudiobbox_t* get_hitbox(int i, int set) const {
    mstudiohitboxset_t const* s = get_hitbox_set(set);
    if (!s)
      return NULL;
    return s->pHitbox(i);
  }
  inline int get_hitbox_count(int set) const {
    mstudiohitboxset_t const* s = get_hitbox_set(set);
    if (!s)
      return 0;
    return s->numhitboxes;
  }
  // file local animations? and sequences
  // private:
  int           numlocalanim;   // animations/poses
  int           localanimindex; // animation descriptions
  int           numlocalseq;    // sequences
  int           localseqindex;
  // private:
  mutable int   activitylistversion; // initialization flag - have the sequences been indexed?
  mutable int   eventsindexed;
  // raw textures
  int           numtextures;
  int           textureindex;
  // raw textures search paths
  int           numcdtextures;
  int           cdtextureindex;
  // replaceable textures tables
  int           numskinref;
  int           numskinfamilies;
  int           skinindex;
  int           numbodyparts;
  int           bodypartindex;
  // queryable attachable points
  // private:
  int           numlocalattachments;
  int           localattachmentindex;
  // animation node to animation node transition graph
  // private:
  int           numlocalnodes;
  int           localnodeindex;
  int           localnodenameindex;
  int           numflexdesc;
  int           flexdescindex;
  int           numflexcontrollers;
  int           flexcontrollerindex;
  int           numflexrules;
  int           flexruleindex;
  int           numikchains;
  int           ikchainindex;
  int           nummouths;
  int           mouthindex;
  // private:
  int           numlocalposeparameters;
  int           localposeparamindex;
  int           surfacepropindex;
  // Key values
  int           keyvalueindex;
  int           keyvaluesize;
  int           numlocalikautoplaylocks;
  int           localikautoplaylockindex;
  // The collision model mass that jay wanted
  float         mass;
  int           contents;
  // external animations, models, etc.
  int           numincludemodels;
  int           includemodelindex;
  // implementation specific back pointer to virtual data
  mutable void* virtualModel;
  // for demand loaded animation blocks
  int           szanimblocknameindex;
  int           numanimblocks;
  int           animblockindex;
  mutable void* animblockModel;
  int           bonetablebynameindex;
  // used by tools only that don't cache, but persist mdl's peer data
  // engine uses virtualModel to back link to cache pointers
  void*         pVertexBase;
  void*         pIndexBase;
  // if STUDIOHDR_FLAGS_CONSTANT_DIRECTIONAL_LIGHT_DOT is set,
  // this value is used to calculate directional components of lighting
  // on static props
  byte          constdirectionallightdot;
  // set during load of mdl data to track *desired* lod configuration (not actual)
  // the *actual* clamped root lod is found in studiohwdata
  // this is stored here as a global store to ensure the staged loading matches the rendering
  byte          rootLOD;
  // set in the mdl data to specify that lod configuration should only allow first numAllowRootLODs
  // to be set as root LOD:
  //	numAllowedRootLODs = 0	means no restriction, any lod can be set as root lod.
  //	numAllowedRootLODs = N	means that lod0 - lod(N-1) can be set as root lod, but not lodN or lower.
  byte          numAllowedRootLODs;
  byte          unused[1];
  int           unused4; // zero out if version < 47
  int           numflexcontrollerui;
  int           flexcontrolleruiindex;
  float         flVertAnimFixedPointScale;
  int           unused3[1];
  // FIXME: Remove when we up the model version. Move all fields of studiohdr2_t into studiohdr_t.
  int           studiohdr2index;
  // NOTE: No room to add stuff? Up the .mdl file format version
  // [and move all fields in studiohdr2_t into studiohdr_t and kill studiohdr2_t],
  // or add your stuff to studiohdr2_t. See NumSrcBoneTransforms/SrcBoneTransform for the pattern to use.
  int           unused2[1];
};

struct light_desc_t {
  light_type   m_Type;
  Vector       m_Color;
  Vector       m_Position;
  Vector       m_Direction;
  float        m_Range;
  float        m_Falloff;
  float        m_Attenuation0;
  float        m_Attenuation1;
  float        m_Attenuation2;
  float        m_Theta;
  float        m_Phi;
  float        m_ThetaDot;
  float        m_PhiDot;
  unsigned int m_Flags;
  float        OneOver_ThetaDot_Minus_PhiDot;
  float        m_RangeSquared;
};

struct draw_model_info_t {
  studiohdr_t*        m_pStudioHdr;
  studiohwdata_t*     m_pHardwareData;
  studio_decal_handle m_Decals;
  int                 m_Skin;
  int                 m_Body;
  int                 m_HitboxSet;
  void*               m_pClientEntity;
  int                 m_Lod;
  color_mesh_info_t*  m_pColorMeshes;
  bool                m_bStaticLighting;
  Vector              m_vecAmbientCube[6];
  int                 m_nLocalLightCount;
  light_desc_t        m_LocalLightDescs[4];
  uint8_t             m_pad_00[1024];
};

struct draw_model_results_t {
  int m_ActualTriCount;
  int m_TextureMemoryBytes;
  int m_NumHardwareBones;
  int m_NumBatches;
  int m_NumMaterials;
  int m_nLODUsed;
  int m_flLODMetric;
};

//-----------------------------------------------------------------------------
// What kind of material override is it?
//-----------------------------------------------------------------------------
enum override_type_t {
  OVERRIDE_NORMAL = 0,
  OVERRIDE_BUILD_SHADOWS,
  OVERRIDE_DEPTH_WRITE,
  OVERRIDE_SSAO_DEPTH_WRITE,
};

//-----------------------------------------------------------------------------
// Shader state flags can be read from the FLAGS materialvar
// Also can be read or written to with the Set/GetMaterialVarFlags() call
// Also make sure you add/remove a string associated with each flag below to CShaderSystem::ShaderStateString
// in ShaderSystem.cpp
//-----------------------------------------------------------------------------
enum material_var_flags_t {
  MATERIAL_VAR_DEBUG = (1 << 0),
  MATERIAL_VAR_NO_DEBUG_OVERRIDE = (1 << 1),
  MATERIAL_VAR_NO_DRAW = (1 << 2),
  MATERIAL_VAR_USE_IN_FILLRATE_MODE = (1 << 3),
  MATERIAL_VAR_VERTEXCOLOR = (1 << 4),
  MATERIAL_VAR_VERTEXALPHA = (1 << 5),
  MATERIAL_VAR_SELFILLUM = (1 << 6),
  MATERIAL_VAR_ADDITIVE = (1 << 7),
  MATERIAL_VAR_ALPHATEST = (1 << 8),
  MATERIAL_VAR_MULTIPASS = (1 << 9),
  MATERIAL_VAR_ZNEARER = (1 << 10),
  MATERIAL_VAR_MODEL = (1 << 11),
  MATERIAL_VAR_FLAT = (1 << 12),
  MATERIAL_VAR_NOCULL = (1 << 13),
  MATERIAL_VAR_NOFOG = (1 << 14),
  MATERIAL_VAR_IGNOREZ = (1 << 15),
  MATERIAL_VAR_DECAL = (1 << 16),
  MATERIAL_VAR_ENVMAPSPHERE = (1 << 17),
  MATERIAL_VAR_NOALPHAMOD = (1 << 18),
  MATERIAL_VAR_ENVMAPCAMERASPACE = (1 << 19),
  MATERIAL_VAR_BASEALPHAENVMAPMASK = (1 << 20),
  MATERIAL_VAR_TRANSLUCENT = (1 << 21),
  MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK = (1 << 22),
  MATERIAL_VAR_NEEDS_SOFTWARE_SKINNING = (1 << 23),
  MATERIAL_VAR_OPAQUETEXTURE = (1 << 24),
  MATERIAL_VAR_ENVMAPMODE = (1 << 25),
  MATERIAL_VAR_SUPPRESS_DECALS = (1 << 26),
  MATERIAL_VAR_HALFLAMBERT = (1 << 27),
  MATERIAL_VAR_WIREFRAME = (1 << 28),
  MATERIAL_VAR_ALLOWALPHATOCOVERAGE = (1 << 29),
  MATERIAL_VAR_IGNORE_ALPHA_MODULATION = (1 << 30),

  // NOTE: Only add flags here that either should be read from
  // .vmts or can be set directly from client code. Other, internal
  // flags should to into the flag enum in imaterialinternal.h
};

class i_material {
public:
  void set_material_var_flag(material_var_flags_t flag, bool state);
};

class c_material_system {
public:
  i_material* find_material(std::string_view name, std::string_view group, bool complain = true,
                            const char* complain_prefix = nullptr);
};

// 29, 28
class c_studio_render {
public:
  void set_color_modulation(const float* color);
  void set_alpha_modulation(float alpha);
  void forced_material_override(i_material* material, override_type_t override_type = OVERRIDE_NORMAL);
};

struct model_t {
  void* fnHandle;
  char* strName;

  int   nLoadFlags;   // mark loaded/not loaded
  int   nServerCount; // marked at load
  i_material**
         ppMaterials; // null-terminated runtime material cache; ((intptr_t*)(ppMaterials))[-1] == nMaterials

  void*  type;
  int    flags; // MODELFLAG_???

  // volume occupied by the model graphics
  Vector mins, maxs;
  float  radius;

  union {
    void* brush;
    void* studio;
    void* sprite;
  };
};

class c_model_info_client {
public:
  model_t*     get_model(int entidx);
  studiohdr_t* get_studio_model(const model_t* model);
};