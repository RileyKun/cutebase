//
// Created by Riley on 4/25/2024.
//

#pragma once

constexpr float TEAM_RED[4] = {1.f, 0.23f, 0.23f, 1.f};
constexpr float TEAM_RED_NOVIS[4] = {0.56f, 0.11f, 0.11f};
constexpr float TEAM_BLU[4] = {0.23f, 0.51f, 1.f, 1.f};
constexpr float TEAM_BLU_NOVIS[4] = {0.13f, 0.33f, 0.64f};
constexpr float TEAM_SPEC[4] = {0.85f, 0.85f, 0.85f, 0.85f};

#define MAX_CMD_BUFFER          4000

#define MAX_NEW_COMMANDS        ((1 << NUM_NEW_COMMAND_BITS) - 1)
#define NUM_BACKUP_COMMAND_BITS 3
#define MAX_BACKUP_COMMANDS     ((1 << NUM_BACKUP_COMMAND_BITS) - 1)
#define MAX_COMMANDS            MAX_NEW_COMMANDS + MAX_BACKUP_COMMANDS

#define MAX_PLAYER_NAME_LENGTH  32
#define SIGNED_GUID_LEN         32 // Hashed CD Key (32 hex alphabetic chars + 0 terminator )

#define SENTRYGUN_MAX_SHELLS_1  150
#define SENTRYGUN_MAX_SHELLS_2  200
#define SENTRYGUN_MAX_SHELLS_3  200
#define SENTRYGUN_MAX_ROCKETS   20

#define DISPSURF_FLAG_SURFACE   (1 << 0)
#define DISPSURF_FLAG_WALKABLE  (1 << 1)
#define DISPSURF_FLAG_BUILDABLE (1 << 2)
#define DISPSURF_FLAG_SURFPROP1 (1 << 3)
#define DISPSURF_FLAG_SURFPROP2 (1 << 4)

#define IN_ATTACK               (1 << 0)
#define IN_JUMP                 (1 << 1)
#define IN_DUCK                 (1 << 2)
#define IN_FORWARD              (1 << 3)
#define IN_BACK                 (1 << 4)
#define IN_USE                  (1 << 5)
#define IN_CANCEL               (1 << 6)
#define IN_LEFT                 (1 << 7)
#define IN_RIGHT                (1 << 8)
#define IN_MOVELEFT             (1 << 9)
#define IN_MOVERIGHT            (1 << 10)
#define IN_ATTACK2              (1 << 11)
#define IN_RUN                  (1 << 12)
#define IN_RELOAD               (1 << 13)
#define IN_ALT1                 (1 << 14)
#define IN_ALT2                 (1 << 15)
#define IN_SCORE                (1 << 16)
#define IN_SPEED                (1 << 17)
#define IN_WALK                 (1 << 18)
#define IN_ZOOM                 (1 << 19)
#define IN_WEAPON1              (1 << 20)
#define IN_WEAPON2              (1 << 21)
#define IN_BULLRUSH             (1 << 22)
#define IN_GRENADE1             (1 << 23)
#define IN_GRENADE2             (1 << 24)
#define IN_ATTACK3              (1 << 25)

#define FL_ONGROUND             (1 << 0)
#define FL_DUCKING              (1 << 1)
#define FL_WATERJUMP            (1 << 2)
#define FL_ONTRAIN              (1 << 3)
#define FL_INRAIN               (1 << 4)
#define FL_FROZEN               (1 << 5)
#define FL_ATCONTROLS           (1 << 6)
#define FL_CLIENT               (1 << 7)
#define FL_FAKECLIENT           (1 << 8)
#define FL_INWATER              (1 << 9)
#define FL_CONVEYOR             (1 << 12)

enum {
  TF_CLASS_UNDEFINED = 0,

  TF_CLASS_SCOUT, // TF_FIRST_NORMAL_CLASS
  TF_CLASS_SNIPER,
  TF_CLASS_SOLDIER,
  TF_CLASS_DEMOMAN,
  TF_CLASS_MEDIC,
  TF_CLASS_HEAVYWEAPONS,
  TF_CLASS_PYRO,
  TF_CLASS_SPY,
  TF_CLASS_ENGINEER,

  // Add any new classes after Engineer
  TF_CLASS_CIVILIAN, // TF_LAST_NORMAL_CLASS
  TF_CLASS_COUNT_ALL,

  TF_CLASS_RANDOM
};

//-----------------------------------------------------------------------------
// Player Classes.
//-----------------------------------------------------------------------------
#define TF_CLASS_COUNT        (TF_CLASS_COUNT_ALL)

#define TF_FIRST_NORMAL_CLASS (TF_CLASS_UNDEFINED + 1)
#define TF_LAST_NORMAL_CLASS  (TF_CLASS_CIVILIAN)

#define TF_CLASS_MENU_BUTTONS (TF_CLASS_RANDOM + 1)

enum e_hitboxes {
  HITBOX_HEAD,
  HITBOX_PELVIS,
  HITBOX_SPINE_0, // stomach
  HITBOX_SPINE_1, // stomach
  HITBOX_SPINE_2, // chest
  HITBOX_SPINE_3, // chest
  HITBOX_UPPERARM_L,
  HITBOX_LOWERARM_L,
  HITBOX_HAND_L,
  HITBOX_UPPERARM_R,
  HITBOX_LOWERARM_R,
  HITBOX_HAND_R,
  HITBOX_HIP_L,
  HITBOX_KNEE_L,
  HITBOX_FOOT_L,
  HITBOX_HIP_R,
  HITBOX_KNEE_R,
  HITBOX_FOOT_R,
  HITBOX_MAX
};

#define BONE_CALCULATE_MASK        0x1F
#define BONE_PHYSICALLY_SIMULATED  0x01 // bone is physically simulated when physics are active
#define BONE_PHYSICS_PROCEDURAL    0x02 // procedural when physics is active
#define BONE_ALWAYS_PROCEDURAL     0x04 // bone is always procedurally animated
#define BONE_SCREEN_ALIGN_SPHERE   0x08 // bone aligns to the screen, not constrained in motion.
#define BONE_SCREEN_ALIGN_CYLINDER 0x10 // bone aligns to the screen, constrained by it's own axis.

#define BONE_USED_MASK             0x0007FF00
#define BONE_USED_BY_ANYTHING      0x0007FF00
#define BONE_USED_BY_HITBOX        0x00000100 // bone (or child) is used by a hit box
#define BONE_USED_BY_ATTACHMENT    0x00000200 // bone (or child) is used by an attachment point
#define BONE_USED_BY_VERTEX_MASK   0x0003FC00
#define BONE_USED_BY_VERTEX_LOD0 \
  0x00000400 // bone (or child) is used by the toplevel model via skinned vertex
#define BONE_USED_BY_VERTEX_LOD1 0x00000800
#define BONE_USED_BY_VERTEX_LOD2 0x00001000
#define BONE_USED_BY_VERTEX_LOD3 0x00002000
#define BONE_USED_BY_VERTEX_LOD4 0x00004000
#define BONE_USED_BY_VERTEX_LOD5 0x00008000
#define BONE_USED_BY_VERTEX_LOD6 0x00010000
#define BONE_USED_BY_VERTEX_LOD7 0x00020000
#define BONE_USED_BY_BONE_MERGE  0x00040000 // bone is available for bone merge to occur against it

//
// NOTE: Inserting to most or all of the enums in this file will BREAK DEMOS -
// please add to the end instead.
//
enum e_weapon_type {
  TF_WEAPON_NONE = 0,
  TF_WEAPON_BAT,
  TF_WEAPON_BAT_WOOD,
  TF_WEAPON_BOTTLE,
  TF_WEAPON_FIREAXE,
  TF_WEAPON_CLUB,
  TF_WEAPON_CROWBAR,
  TF_WEAPON_KNIFE,
  TF_WEAPON_FISTS,
  TF_WEAPON_SHOVEL,
  TF_WEAPON_WRENCH,
  TF_WEAPON_BONESAW,
  TF_WEAPON_SHOTGUN_PRIMARY,
  TF_WEAPON_SHOTGUN_SOLDIER,
  TF_WEAPON_SHOTGUN_HWG,
  TF_WEAPON_SHOTGUN_PYRO,
  TF_WEAPON_SCATTERGUN,
  TF_WEAPON_SNIPERRIFLE,
  TF_WEAPON_MINIGUN,
  TF_WEAPON_SMG,
  TF_WEAPON_SYRINGEGUN_MEDIC,
  TF_WEAPON_TRANQ,
  TF_WEAPON_ROCKETLAUNCHER,
  TF_WEAPON_GRENADELAUNCHER,
  TF_WEAPON_PIPEBOMBLAUNCHER,
  TF_WEAPON_FLAMETHROWER,
  TF_WEAPON_GRENADE_NORMAL,
  TF_WEAPON_GRENADE_CONCUSSION,
  TF_WEAPON_GRENADE_NAIL,
  TF_WEAPON_GRENADE_MIRV,
  TF_WEAPON_GRENADE_MIRV_DEMOMAN,
  TF_WEAPON_GRENADE_NAPALM,
  TF_WEAPON_GRENADE_GAS,
  TF_WEAPON_GRENADE_EMP,
  TF_WEAPON_GRENADE_CALTROP,
  TF_WEAPON_GRENADE_PIPEBOMB,
  TF_WEAPON_GRENADE_SMOKE_BOMB,
  TF_WEAPON_GRENADE_HEAL,
  TF_WEAPON_GRENADE_STUNBALL,
  TF_WEAPON_GRENADE_JAR,
  TF_WEAPON_GRENADE_JAR_MILK,
  TF_WEAPON_PISTOL,
  TF_WEAPON_PISTOL_SCOUT,
  TF_WEAPON_REVOLVER,
  TF_WEAPON_NAILGUN,
  TF_WEAPON_PDA,
  TF_WEAPON_PDA_ENGINEER_BUILD,
  TF_WEAPON_PDA_ENGINEER_DESTROY,
  TF_WEAPON_PDA_SPY,
  TF_WEAPON_BUILDER,
  TF_WEAPON_MEDIGUN,
  TF_WEAPON_GRENADE_MIRVBOMB,
  TF_WEAPON_FLAMETHROWER_ROCKET,
  TF_WEAPON_GRENADE_DEMOMAN,
  TF_WEAPON_SENTRY_BULLET,
  TF_WEAPON_SENTRY_ROCKET,
  TF_WEAPON_DISPENSER,
  TF_WEAPON_INVIS,
  TF_WEAPON_FLAREGUN,
  TF_WEAPON_LUNCHBOX,
  TF_WEAPON_JAR,
  TF_WEAPON_COMPOUND_BOW,
  TF_WEAPON_BUFF_ITEM,
  TF_WEAPON_PUMPKIN_BOMB,
  TF_WEAPON_SWORD,
  TF_WEAPON_ROCKETLAUNCHER_DIRECTHIT,
  TF_WEAPON_LIFELINE,
  TF_WEAPON_LASER_POINTER,
  TF_WEAPON_DISPENSER_GUN,
  TF_WEAPON_SENTRY_REVENGE,
  TF_WEAPON_JAR_MILK,
  TF_WEAPON_HANDGUN_SCOUT_PRIMARY,
  TF_WEAPON_BAT_FISH,
  TF_WEAPON_CROSSBOW,
  TF_WEAPON_STICKBOMB,
  TF_WEAPON_HANDGUN_SCOUT_SECONDARY,
  TF_WEAPON_SODA_POPPER,
  TF_WEAPON_SNIPERRIFLE_DECAP,
  TF_WEAPON_RAYGUN,
  TF_WEAPON_PARTICLE_CANNON,
  TF_WEAPON_MECHANICAL_ARM,
  TF_WEAPON_DRG_POMSON,
  TF_WEAPON_BAT_GIFTWRAP,
  TF_WEAPON_GRENADE_ORNAMENT_BALL,
  TF_WEAPON_FLAREGUN_REVENGE,
  TF_WEAPON_PEP_BRAWLER_BLASTER,
  TF_WEAPON_CLEAVER,
  TF_WEAPON_GRENADE_CLEAVER,
  TF_WEAPON_STICKY_BALL_LAUNCHER,
  TF_WEAPON_GRENADE_STICKY_BALL,
  TF_WEAPON_SHOTGUN_BUILDING_RESCUE,
  TF_WEAPON_CANNON,
  TF_WEAPON_THROWABLE,
  TF_WEAPON_GRENADE_THROWABLE,
  TF_WEAPON_PDA_SPY_BUILD,
  TF_WEAPON_GRENADE_WATERBALLOON,
  TF_WEAPON_HARVESTER_SAW,
  TF_WEAPON_SPELLBOOK,
  TF_WEAPON_SPELLBOOK_PROJECTILE,
  TF_WEAPON_SNIPERRIFLE_CLASSIC,
  TF_WEAPON_PARACHUTE,
  TF_WEAPON_GRAPPLINGHOOK,
  TF_WEAPON_PASSTIME_GUN,
  TF_WEAPON_CHARGED_SMG,
  //
  // ADD NEW WEAPONS HERE TO AVOID BREAKING DEMOS
  //
  TF_WEAPON_COUNT
};

enum struct e_class_ids : int {
  CAI_BaseNPC,
  CBaseAnimating,
  CBaseAnimatingOverlay,
  CBaseAttributableItem,
  CBaseCombatCharacter,
  CBaseCombatWeapon,
  CBaseDoor,
  CBaseEntity,
  CBaseFlex,
  CBaseGrenade,
  CBaseObject,
  CBaseObjectUpgrade,
  CBaseParticleEntity,
  CBasePlayer,
  CBaseProjectile,
  CBasePropDoor,
  CBaseTeamObjectiveResource,
  CBaseTempEntity,
  CBaseViewModel,
  CBeam,
  CBoneFollower,
  CBonusDuckPickup,
  CBonusPack,
  CBonusRoundLogic,
  CBreakableProp,
  CBreakableSurface,
  CCaptureFlag,
  CCaptureFlagReturnIcon,
  CCaptureZone,
  CColorCorrection,
  CColorCorrectionVolume,
  CCurrencyPack,
  CDynamicLight,
  CDynamicProp,
  CEconEntity,
  CEconWearable,
  CEmbers,
  CEntityDissolve,
  CEntityFlame,
  CEntityParticleTrail,
  CEnvDetailController,
  CEnvParticleScript,
  CEnvProjectedTexture,
  CEnvQuadraticBeam,
  CEnvScreenEffect,
  CEnvScreenOverlay,
  CEnvTonemapController,
  CEnvWind,
  CEyeballBoss,
  CFireSmoke,
  CFireTrail,
  CFish,
  CFogController,
  CFunc_Dust,
  CFunc_LOD,
  CFuncAreaPortalWindow,
  CFuncConveyor,
  CFuncForceField,
  CFuncLadder,
  CFuncMonitor,
  CFuncOccluder,
  CFuncPasstimeGoal,
  CFuncReflectiveGlass,
  CFuncRespawnRoom,
  CFuncRespawnRoomVisualizer,
  CFuncRotating,
  CFuncSmokeVolume,
  CFuncTrackTrain,
  CGameRulesProxy,
  CHalloweenGiftPickup,
  CHalloweenPickup,
  CHalloweenSoulPack,
  CHandleTest,
  CHeadlessHatman,
  CHightower_TeleportVortex,
  CInfoLadderDismount,
  CInfoLightingRelative,
  CInfoOverlayAccessor,
  CLaserDot,
  CLightGlow,
  CMannVsMachineStats,
  CMaterialModifyControl,
  CMerasmus,
  CMerasmusDancer,
  CMonsterResource,
  CObjectCartDispenser,
  CObjectDispenser,
  CObjectSapper,
  CObjectSentrygun,
  CObjectTeleporter,
  CParticleFire,
  CParticlePerformanceMonitor,
  CParticleSystem,
  CPasstimeBall,
  CPasstimeGun,
  CPhysBox,
  CPhysBoxMultiplayer,
  CPhysicsProp,
  CPhysicsPropMultiplayer,
  CPhysMagnet,
  CPlasma,
  CPlayerDestructionDispenser,
  CPlayerResource,
  CPointCamera,
  CPointCommentaryNode,
  CPointWorldText,
  CPoseController,
  CPrecipitation,
  CPropVehicleDriveable,
  CRagdollManager,
  CRagdollProp,
  CRagdollPropAttached,
  CRobotDispenser,
  CRopeKeyframe,
  CSceneEntity,
  CShadowControl,
  CSlideshowDisplay,
  CSmokeStack,
  CSniperDot,
  CSpotlightEnd,
  CSprite,
  CSpriteOriented,
  CSpriteTrail,
  CSteamJet,
  CSun,
  CTeam,
  CTeamplayRoundBasedRulesProxy,
  CTeamRoundTimer,
  CTeamTrainWatcher,
  CTEArmorRicochet,
  CTEBaseBeam,
  CTEBeamEntPoint,
  CTEBeamEnts,
  CTEBeamFollow,
  CTEBeamLaser,
  CTEBeamPoints,
  CTEBeamRing,
  CTEBeamRingPoint,
  CTEBeamSpline,
  CTEBloodSprite,
  CTEBloodStream,
  CTEBreakModel,
  CTEBSPDecal,
  CTEBubbles,
  CTEBubbleTrail,
  CTEClientProjectile,
  CTEDecal,
  CTEDust,
  CTEDynamicLight,
  CTEEffectDispatch,
  CTEEnergySplash,
  CTEExplosion,
  CTEFireBullets,
  CTEFizz,
  CTEFootprintDecal,
  CTEGaussExplosion,
  CTEGlowSprite,
  CTEImpact,
  CTEKillPlayerAttachments,
  CTELargeFunnel,
  CTeleportVortex,
  CTEMetalSparks,
  CTEMuzzleFlash,
  CTEParticleSystem,
  CTEPhysicsProp,
  CTEPlayerAnimEvent,
  CTEPlayerDecal,
  CTEProjectedDecal,
  CTEShatterSurface,
  CTEShowLine,
  CTesla,
  CTESmoke,
  CTESparks,
  CTESprite,
  CTESpriteSpray,
  CTest_ProxyToggle_Networkable,
  CTestTraceline,
  CTETFBlood,
  CTETFExplosion,
  CTETFParticleEffect,
  CTEWorldDecal,
  CTFAmmoPack,
  CTFBall_Ornament,
  CTFBaseBoss,
  CTFBaseProjectile,
  CTFBaseRocket,
  CTFBat,
  CTFBat_Fish,
  CTFBat_Giftwrap,
  CTFBat_Wood,
  CTFBonesaw,
  CTFBotHintEngineerNest,
  CTFBottle,
  CTFBreakableMelee,
  CTFBreakableSign,
  CTFBuffItem,
  CTFCannon,
  CTFChargedSMG,
  CTFCleaver,
  CTFClub,
  CTFCompoundBow,
  CTFCrossbow,
  CTFDRGPomson,
  CTFDroppedWeapon,
  CTFFireAxe,
  CTFFists,
  CTFFlameManager,
  CTFFlameRocket,
  CTFFlameThrower,
  CTFFlareGun,
  CTFFlareGun_Revenge,
  CTFGameRulesProxy,
  CTFGasManager,
  CTFGenericBomb,
  CTFGlow,
  CTFGrapplingHook,
  CTFGrenadeLauncher,
  CTFGrenadePipebombProjectile,
  CTFHalloweenMinigame,
  CTFHalloweenMinigame_FallingPlatforms,
  CTFHellZap,
  CTFItem,
  CTFJar,
  CTFJarGas,
  CTFJarMilk,
  CTFKatana,
  CTFKnife,
  CTFLaserPointer,
  CTFLunchBox,
  CTFLunchBox_Drink,
  CTFMechanicalArm,
  CTFMedigunShield,
  CTFMiniGame,
  CTFMinigameLogic,
  CTFMinigun,
  CTFObjectiveResource,
  CTFParachute,
  CTFParachute_Primary,
  CTFParachute_Secondary,
  CTFParticleCannon,
  CTFPasstimeLogic,
  CTFPEPBrawlerBlaster,
  CTFPipebombLauncher,
  CTFPistol,
  CTFPistol_Scout,
  CTFPistol_ScoutPrimary,
  CTFPistol_ScoutSecondary,
  CTFPlayer,
  CTFPlayerDestructionLogic,
  CTFPlayerResource,
  CTFPointManager,
  CTFPowerupBottle,
  CTFProjectile_Arrow,
  CTFProjectile_BallOfFire,
  CTFProjectile_Cleaver,
  CTFProjectile_EnergyBall,
  CTFProjectile_EnergyRing,
  CTFProjectile_Flare,
  CTFProjectile_GrapplingHook,
  CTFProjectile_HealingBolt,
  CTFProjectile_Jar,
  CTFProjectile_JarGas,
  CTFProjectile_JarMilk,
  CTFProjectile_MechanicalArmOrb,
  CTFProjectile_Rocket,
  CTFProjectile_SentryRocket,
  CTFProjectile_SpellBats,
  CTFProjectile_SpellFireball,
  CTFProjectile_SpellKartBats,
  CTFProjectile_SpellKartOrb,
  CTFProjectile_SpellLightningOrb,
  CTFProjectile_SpellMeteorShower,
  CTFProjectile_SpellMirv,
  CTFProjectile_SpellPumpkin,
  CTFProjectile_SpellSpawnBoss,
  CTFProjectile_SpellSpawnHorde,
  CTFProjectile_SpellSpawnZombie,
  CTFProjectile_SpellTransposeTeleport,
  CTFProjectile_Throwable,
  CTFProjectile_ThrowableBreadMonster,
  CTFProjectile_ThrowableBrick,
  CTFProjectile_ThrowableRepel,
  CTFPumpkinBomb,
  CTFRagdoll,
  CTFRaygun,
  CTFReviveMarker,
  CTFRevolver,
  CTFRobotArm,
  CTFRobotDestruction_Robot,
  CTFRobotDestruction_RobotGroup,
  CTFRobotDestruction_RobotSpawn,
  CTFRobotDestructionLogic,
  CTFRocketLauncher,
  CTFRocketLauncher_AirStrike,
  CTFRocketLauncher_DirectHit,
  CTFRocketLauncher_Mortar,
  CTFRocketPack,
  CTFScatterGun,
  CTFShotgun,
  CTFShotgun_HWG,
  CTFShotgun_Pyro,
  CTFShotgun_Revenge,
  CTFShotgun_Soldier,
  CTFShotgunBuildingRescue,
  CTFShovel,
  CTFSlap,
  CTFSMG,
  CTFSniperRifle,
  CTFSniperRifleClassic,
  CTFSniperRifleDecap,
  CTFSodaPopper,
  CTFSpellBook,
  CTFStickBomb,
  CTFStunBall,
  CTFSword,
  CTFSyringeGun,
  CTFTankBoss,
  CTFTauntProp,
  CTFTeam,
  CTFThrowable,
  CTFViewModel,
  CTFWeaponBase,
  CTFWeaponBaseGrenadeProj,
  CTFWeaponBaseGun,
  CTFWeaponBaseMelee,
  CTFWeaponBaseMerasmusGrenade,
  CTFWeaponBuilder,
  CTFWeaponFlameBall,
  CTFWeaponInvis,
  CTFWeaponPDA,
  CTFWeaponPDA_Engineer_Build,
  CTFWeaponPDA_Engineer_Destroy,
  CTFWeaponPDA_Spy,
  CTFWeaponPDAExpansion_Dispenser,
  CTFWeaponPDAExpansion_Teleporter,
  CTFWeaponSapper,
  CTFWearable,
  CTFWearableCampaignItem,
  CTFWearableDemoShield,
  CTFWearableItem,
  CTFWearableLevelableItem,
  CTFWearableRazorback,
  CTFWearableRobotArm,
  CTFWearableVM,
  CTFWrench,
  CVGuiScreen,
  CVoteController,
  CWaterBullet,
  CWaterLODControl,
  CWeaponIFMBase,
  CWeaponIFMBaseCamera,
  CWeaponIFMSteadyCam,
  CWeaponMedigun,
  CWorld,
  CZombie,
  DustTrail,
  MovieExplosion,
  NextBotCombatCharacter,
  ParticleSmokeGrenade,
  RocketTrail,
  SmokeTrail,
  SporeExplosion,
  SporeTrail,
};

#define DISPENSER_MAX_METAL_AMMO      400
#define MAX_DISPENSER_HEALING_TARGETS 32
#define MINI_DISPENSER_MAX_METAL      200

enum {
  OBS_MODE_NONE = 0,  // not in spectator mode
  OBS_MODE_DEATHCAM,  // special mode for death cam animation
  OBS_MODE_FREEZECAM, // zooms to a target, and freeze-frames on them
  OBS_MODE_FIXED,     // view from a fixed camera position
  OBS_MODE_IN_EYE,    // follow a player in first person view
  OBS_MODE_CHASE,     // follow a player in third person view
  OBS_MODE_POI, // PASSTIME point of interest - game objective, big fight, anything interesting; added in the
                // middle of the enum due to tons of hard-coded "<ROAMING" enum compares
  OBS_MODE_ROAMING, // free roaming

  NUM_OBSERVER_MODES
};

enum ETFConds {
  TFCond_Slowed = (1 << 0),      // Toggled when a player is slowed down.
  TFCond_Zoomed = (1 << 1),      // Toggled when a player is zoomed.
  TFCond_Disguising = (1 << 2),  // Toggled when a Spy is disguising.
  TFCond_Disguised = (1 << 3),   // Toggled when a Spy is disguised.
  TFCond_Cloaked = (1 << 4),     // Toggled when a Spy is invisible.
  TFCond_Ubercharged = (1 << 5), // Toggled when a player is UberCharged.
  TFCond_TeleportedGlow =
      (1 << 6),               // Toggled when someone leaves a teleporter and has glow beneath their feet.
  TFCond_Taunting = (1 << 7), // Toggled when a player is taunting.
  TFCond_UberchargeFading = (1 << 8), // Toggled when the UberCharge is fading.
  TFCond_CloakFlicker = (1 << 9),     // Toggled when a Spy is visible during cloak.
  TFCond_Teleporting =
      (1 << 10), // Only activates for a brief second when the player is being teleported; not very useful.
  TFCond_Kritzkrieged = (1 << 11),   // Toggled when a player is being crit buffed by the KritzKrieg.
  TFCond_TmpDamageBonus = (1 << 12), // Unknown what this is for. Name taken from the AlliedModders SDK.
  TFCond_DeadRingered = (1 << 13),   // Toggled when a player is taking reduced damage from the Deadringer.
  TFCond_Bonked = (1 << 14),         // Toggled when a player is under the effects of The Bonk! Atomic Punch.
  TFCond_Stunned = (1 << 15),  // Toggled when a player's speed is reduced from airblast or a Sandman ball.
  TFCond_Buffed = (1 << 16),   // Toggled when a player is within range of an activated Buff Banner.
  TFCond_Charging = (1 << 17), // Toggled when a Demoman charges with the shield.
  TFCond_DemoBuff = (1 << 18), // Toggled when a Demoman has heads from the Eyelander.
  TFCond_CritCola = (1 << 19), // Toggled when the player is under the effect of The Crit-a-Cola.
  TFCond_InHealRadius = (1 << 20), // Unused condition, name taken from AlliedModders SDK.
  TFCond_Healing = (1 << 21),      // Toggled when someone is being healed by a medic or a dispenser.
  TFCond_OnFire = (1 << 22),       // Toggled when a player is on fire.
  TFCond_Overhealed = (1 << 23),   // Toggled when a player has >100% health.
  TFCond_Jarated = (1 << 24),      // Toggled when a player is hit with a Sniper's Jarate.
  TFCond_Bleeding = (1 << 25),     // Toggled when a player is taking bleeding damage.
  TFCond_DefenseBuffed =
      (1 << 26),                  // Toggled when a player is within range of an activated Battalion's Backup.
  TFCond_Milked = (1 << 27),      // Player was hit with a jar of Mad Milk.
  TFCond_MegaHeal = (1 << 28),    // Player is under the effect of Quick-Fix charge.
  TFCond_RegenBuffed = (1 << 29), // Toggled when a player is within a Concheror's range.
  TFCond_MarkedForDeath =
      (1 << 30), // Player is marked for death by a Fan O'War hit. Effects are similar to TFCond_Jarated.
  TFCond_NoHealingDamageBuff = (1 << 31),      // Unknown what this is used for.
  TFCondEx_SpeedBuffAlly = (1 << 0),           // Toggled when a player gets hit with the disciplinary action.
  TFCondEx_HalloweenCritCandy = (1 << 1),      // Only for Scream Fortress event maps that drop crit candy.
  TFCondEx_CritCanteen = (1 << 2),             // Player is getting a crit boost from a MVM canteen.
  TFCondEx_CritDemoCharge = (1 << 3),          // From demo's shield
  TFCondEx_CritHype = (1 << 4),                // Soda Popper crits.
  TFCondEx_CritOnFirstBlood = (1 << 5),        // Arena first blood crit buff.
  TFCondEx_CritOnWin = (1 << 6),               // End of round crits.
  TFCondEx_CritOnFlagCapture = (1 << 7),       // CTF intelligence capture crits.
  TFCondEx_CritOnKill = (1 << 8),              // Unknown what this is for.
  TFCondEx_RestrictToMelee = (1 << 9),         // Unknown what this is for.
  TFCondEx_DefenseBuffNoCritBlock = (1 << 10), // MvM Buff.
  TFCondEx_Reprogrammed = (1 << 11),           // MvM Bot has been reprogrammed.
  TFCondEx_PyroCrits = (1 << 12),              // Player is getting crits from the Mmmph charge.
  TFCondEx_PyroHeal = (1 << 13),               // Player is being healed from the Mmmph charge.
  TFCondEx_FocusBuff = (1 << 14),              // Player is getting a focus buff.
  TFCondEx_DisguisedRemoved = (1 << 15),       // Disguised remove from a bot.
  TFCondEx_MarkedForDeathSilent =
      (1 << 16), // Player is under the effects of the Escape Plan/Equalizer or GRU.
  TFCondEx_DisguisedAsDispenser = (1 << 17), // Bot is disguised as dispenser.
  TFCondEx_InKart = (1 << 18),               // MvM bot is being sapped.
  TFCondEx_UberchargedHidden = (1 << 19),    // MvM Related
  TFCondEx_UberchargedCanteen = (1 << 20),   // Player is receiving UberCharge from a canteen.
  TFCondEx_HalloweenBombHead = (1 << 21),    // Player has a bomb on their head from Merasmus.
  TFCondEx_HalloweenThriller = (1 << 22),    // Players are forced to dance from Merasmus.
  TFCondEx_BulletCharge = (1 << 26),         // Player is receiving 75% reduced damage from bullets.
  TFCondEx_ExplosiveCharge = (1 << 27),      // Player is receiving 75% reduced damage from explosives.
  TFCondEx_FireCharge = (1 << 28),           // Player is receiving 75% reduced damage from fire.
  TFCondEx_BulletResistance = (1 << 29),     // Player is receiving 10% reduced damage from bullets.
  TFCondEx_ExplosiveResistance = (1 << 30),  // Player is receiving 10% reduced damage from explosives.
  TFCondEx_FireResistance = (1 << 31),       // Player is receiving 10% reduced damage from fire.
  TFCondEx2_Stealthed = (1 << 0),
  TFCondEx2_MedigunDebuff = (1 << 1),
  TFCondEx2_StealthedUserBuffFade = (1 << 2),
  TFCondEx2_BulletImmune = (1 << 3),
  TFCondEx2_BlastImmune = (1 << 4),
  TFCondEx2_FireImmune = (1 << 5),
  TFCondEx2_PreventDeath = (1 << 6),
  TFCondEx2_MVMBotRadiowave = (1 << 7),
  TFCondEx2_HalloweenSpeedBoost = (1 << 8), // Wheel has granted player speed boost.
  TFCondEx2_HalloweenQuickHeal = (1 << 9),  // Wheel has granted player quick heal.
  TFCondEx2_HalloweenGiant = (1 << 10),     // Wheel has granted player giant mode.
  TFCondEx2_HalloweenTiny = (1 << 11),      // Wheel has granted player tiny mode.
  TFCondEx2_HalloweenInHell = (1 << 12),    // Wheel has granted player in hell mode.
  TFCondEx2_HalloweenGhostMode = (1 << 13), // Wheel has granted player ghost mode.
  TFCondEx2_Parachute = (1 << 16),          // Player has deployed the BASE Jumper.
  TFCondEx2_BlastJumping = (1 << 17),       // Player has sticky or rocket jumped.
  TFCond_MiniCrits = (TFCond_Buffed | TFCond_CritCola),
  TFCond_IgnoreStates = (TFCond_Ubercharged | TFCond_Bonked),
  TFCondEx_IgnoreStates = (TFCondEx_PyroHeal)
};

enum ETFCond {
  TF_COND_INVALID = -1,
  TF_COND_AIMING,
  TF_COND_ZOOMED,
  TF_COND_DISGUISING,
  TF_COND_DISGUISED,
  TF_COND_STEALTHED,
  TF_COND_INVULNERABLE,
  TF_COND_TELEPORTED,
  TF_COND_TAUNTING,
  TF_COND_INVULNERABLE_WEARINGOFF,
  TF_COND_STEALTHED_BLINK,
  TF_COND_SELECTED_TO_TELEPORT,
  TF_COND_CRITBOOSTED,
  TF_COND_TMPDAMAGEBONUS,
  TF_COND_FEIGN_DEATH,
  TF_COND_PHASE,
  TF_COND_STUNNED,
  TF_COND_OFFENSEBUFF,
  TF_COND_SHIELD_CHARGE,
  TF_COND_DEMO_BUFF,
  TF_COND_ENERGY_BUFF,
  TF_COND_RADIUSHEAL,
  TF_COND_HEALTH_BUFF,
  TF_COND_BURNING,
  TF_COND_HEALTH_OVERHEALED,
  TF_COND_URINE,
  TF_COND_BLEEDING,
  TF_COND_DEFENSEBUFF,
  TF_COND_MAD_MILK,
  TF_COND_MEGAHEAL,
  TF_COND_REGENONDAMAGEBUFF,
  TF_COND_MARKEDFORDEATH,
  TF_COND_NOHEALINGDAMAGEBUFF,
  TF_COND_SPEED_BOOST,
  TF_COND_CRITBOOSTED_PUMPKIN,
  TF_COND_CRITBOOSTED_USER_BUFF,
  TF_COND_CRITBOOSTED_DEMO_CHARGE,
  TF_COND_SODAPOPPER_HYPE,
  TF_COND_CRITBOOSTED_FIRST_BLOOD,
  TF_COND_CRITBOOSTED_BONUS_TIME,
  TF_COND_CRITBOOSTED_CTF_CAPTURE,
  TF_COND_CRITBOOSTED_ON_KILL,
  TF_COND_CANNOT_SWITCH_FROM_MELEE,
  TF_COND_DEFENSEBUFF_NO_CRIT_BLOCK,
  TF_COND_REPROGRAMMED,
  TF_COND_CRITBOOSTED_RAGE_BUFF,
  TF_COND_DEFENSEBUFF_HIGH,
  TF_COND_SNIPERCHARGE_RAGE_BUFF,
  TF_COND_DISGUISE_WEARINGOFF,
  TF_COND_MARKEDFORDEATH_SILENT,
  TF_COND_DISGUISED_AS_DISPENSER,
  TF_COND_SAPPED,
  TF_COND_INVULNERABLE_HIDE_UNLESS_DAMAGE,
  TF_COND_INVULNERABLE_USER_BUFF,
  TF_COND_HALLOWEEN_BOMB_HEAD,
  TF_COND_HALLOWEEN_THRILLER,
  TF_COND_RADIUSHEAL_ON_DAMAGE,
  TF_COND_CRITBOOSTED_CARD_EFFECT,
  TF_COND_INVULNERABLE_CARD_EFFECT,
  TF_COND_MEDIGUN_UBER_BULLET_RESIST,
  TF_COND_MEDIGUN_UBER_BLAST_RESIST,
  TF_COND_MEDIGUN_UBER_FIRE_RESIST,
  TF_COND_MEDIGUN_SMALL_BULLET_RESIST,
  TF_COND_MEDIGUN_SMALL_BLAST_RESIST,
  TF_COND_MEDIGUN_SMALL_FIRE_RESIST,
  TF_COND_STEALTHED_USER_BUFF,
  TF_COND_MEDIGUN_DEBUFF,
  TF_COND_STEALTHED_USER_BUFF_FADING,
  TF_COND_BULLET_IMMUNE,
  TF_COND_BLAST_IMMUNE,
  TF_COND_FIRE_IMMUNE,
  TF_COND_PREVENT_DEATH,
  TF_COND_MVM_BOT_STUN_RADIOWAVE,
  TF_COND_HALLOWEEN_SPEED_BOOST,
  TF_COND_HALLOWEEN_QUICK_HEAL,
  TF_COND_HALLOWEEN_GIANT,
  TF_COND_HALLOWEEN_TINY,
  TF_COND_HALLOWEEN_IN_HELL,
  TF_COND_HALLOWEEN_GHOST_MODE,
  TF_COND_MINICRITBOOSTED_ON_KILL,
  TF_COND_OBSCURED_SMOKE,
  TF_COND_PARACHUTE_ACTIVE,
  TF_COND_BLASTJUMPING,
  TF_COND_HALLOWEEN_KART,
  TF_COND_HALLOWEEN_KART_DASH,
  TF_COND_BALLOON_HEAD,
  TF_COND_MELEE_ONLY,
  TF_COND_SWIMMING_CURSE,
  TF_COND_FREEZE_INPUT,
  TF_COND_HALLOWEEN_KART_CAGE,
  TF_COND_DONOTUSE_0,
  TF_COND_RUNE_STRENGTH,
  TF_COND_RUNE_HASTE,
  TF_COND_RUNE_REGEN,
  TF_COND_RUNE_RESIST,
  TF_COND_RUNE_VAMPIRE,
  TF_COND_RUNE_REFLECT,
  TF_COND_RUNE_PRECISION,
  TF_COND_RUNE_AGILITY,
  TF_COND_GRAPPLINGHOOK,
  TF_COND_GRAPPLINGHOOK_SAFEFALL,
  TF_COND_GRAPPLINGHOOK_LATCHED,
  TF_COND_GRAPPLINGHOOK_BLEEDING,
  TF_COND_AFTERBURN_IMMUNE,
  TF_COND_RUNE_KNOCKOUT,
  TF_COND_RUNE_IMBALANCE,
  TF_COND_CRITBOOSTED_RUNE_TEMP,
  TF_COND_PASSTIME_INTERCEPTION,
  TF_COND_SWIMMING_NO_EFFECTS,
  TF_COND_PURGATORY,
  TF_COND_RUNE_KING,
  TF_COND_RUNE_PLAGUE,
  TF_COND_RUNE_SUPERNOVA,
  TF_COND_PLAGUE,
  TF_COND_KING_BUFFED,
  TF_COND_TEAM_GLOWS,
  TF_COND_KNOCKED_INTO_AIR,
  TF_COND_COMPETITIVE_WINNER,
  TF_COND_COMPETITIVE_LOSER,
  TF_COND_HEALING_DEBUFF,
  TF_COND_PASSTIME_PENALTY_DEBUFF,
  TF_COND_GRAPPLED_TO_PLAYER,
  TF_COND_GRAPPLED_BY_PLAYER,
  TF_COND_PARACHUTE_DEPLOYED,
  TF_COND_GAS,
  TF_COND_BURNING_PYRO,
  TF_COND_ROCKETPACK,
  TF_COND_LOST_FOOTING,
  TF_COND_AIR_CURRENT,
  TF_COND_HALLOWEEN_HELL_HEAL,
  TF_COND_POWERUPMODE_DOMINANT
};

// contents flags are seperate bits
// a given brush can contribute multiple content bits
// multiple brushes can be in a single leaf

// these definitions also need to be in q_shared.h!

// lower bits are stronger, and will eat weaker brushes completely
#define CONTENTS_EMPTY                0 // No contents

#define CONTENTS_SOLID                0x1 // an eye is never valid in a solid
#define CONTENTS_WINDOW               0x2 // translucent, but not watery (glass)
#define CONTENTS_AUX                  0x4
#define CONTENTS_GRATE                0x8 // alpha-tested "grate" textures.  Bullets/sight pass through, but solids don't
#define CONTENTS_SLIME                0x10
#define CONTENTS_WATER                0x20
#define CONTENTS_BLOCKLOS             0x40 // block AI line of sight
#define CONTENTS_OPAQUE               0x80 // things that cannot be seen through (may be non-solid though)
#define LAST_VISIBLE_CONTENTS         0x80

#define ALL_VISIBLE_CONTENTS          (LAST_VISIBLE_CONTENTS | (LAST_VISIBLE_CONTENTS - 1))

#define CONTENTS_TESTFOGVOLUME        0x100
#define CONTENTS_UNUSED               0x200

// unused
// NOTE: If it's visible, grab from the top + update LAST_VISIBLE_CONTENTS
// if not visible, then grab from the bottom.
#define CONTENTS_UNUSED6              0x400

#define CONTENTS_TEAM1                0x800  // per team contents used to differentiate collisions
#define CONTENTS_TEAM2                0x1000 // between players and objects on different teams

// ignore CONTENTS_OPAQUE on surfaces that have SURF_NODRAW
#define CONTENTS_IGNORE_NODRAW_OPAQUE 0x2000

// hits entities which are MOVETYPE_PUSH (doors, plats, etc.)
#define CONTENTS_MOVEABLE             0x4000

// remaining contents are non-visible, and don't eat brushes
#define CONTENTS_AREAPORTAL           0x8000

#define CONTENTS_PLAYERCLIP           0x10000
#define CONTENTS_MONSTERCLIP          0x20000

// currents can be added to any other contents, and may be mixed
#define CONTENTS_CURRENT_0            0x40000
#define CONTENTS_CURRENT_90           0x80000
#define CONTENTS_CURRENT_180          0x100000
#define CONTENTS_CURRENT_270          0x200000
#define CONTENTS_CURRENT_UP           0x400000
#define CONTENTS_CURRENT_DOWN         0x800000

#define CONTENTS_ORIGIN               0x1000000 // removed before bsping an entity

#define CONTENTS_MONSTER              0x2000000 // should never be on a brush, only in game
#define CONTENTS_DEBRIS               0x4000000
#define CONTENTS_DETAIL               0x8000000  // brushes to be added after vis leafs
#define CONTENTS_TRANSLUCENT          0x10000000 // auto set if any surface has trans
#define CONTENTS_LADDER               0x20000000
#define CONTENTS_HITBOX               0x40000000 // use accurate hitboxes on trace

// -----------------------------------------------------
// spatial content masks - used for spatial queries (traceline,etc.)
// -----------------------------------------------------
#define MASK_ALL                      (0xFFFFFFFF)
// everything that is normally solid
#define MASK_SOLID                    (CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_MONSTER | CONTENTS_GRATE)
// everything that blocks player movement
#define MASK_PLAYERSOLID                                                                           \
  (CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_PLAYERCLIP | CONTENTS_WINDOW | CONTENTS_MONSTER | \
   CONTENTS_GRATE)
// blocks npc movement
#define MASK_NPCSOLID                                                                               \
  (CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTERCLIP | CONTENTS_WINDOW | CONTENTS_MONSTER | \
   CONTENTS_GRATE)
// water physics in these contents
#define MASK_WATER             (CONTENTS_WATER | CONTENTS_MOVEABLE | CONTENTS_SLIME)
// everything that blocks lighting
#define MASK_OPAQUE            (CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_OPAQUE)
// everything that blocks lighting, but with monsters added.
#define MASK_OPAQUE_AND_NPCS   (MASK_OPAQUE | CONTENTS_MONSTER)
// everything that blocks line of sight for AI
#define MASK_BLOCKLOS          (CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_BLOCKLOS)
// everything that blocks line of sight for AI plus NPCs
#define MASK_BLOCKLOS_AND_NPCS (MASK_BLOCKLOS | CONTENTS_MONSTER)
// everything that blocks line of sight for players
#define MASK_VISIBLE           (MASK_OPAQUE | CONTENTS_IGNORE_NODRAW_OPAQUE)
// everything that blocks line of sight for players, but with monsters added.
#define MASK_VISIBLE_AND_NPCS  (MASK_OPAQUE_AND_NPCS | CONTENTS_IGNORE_NODRAW_OPAQUE)
// bullets see these as solid
#define MASK_SHOT                                                                              \
  (CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTER | CONTENTS_WINDOW | CONTENTS_DEBRIS | \
   CONTENTS_HITBOX)
// non-raycasted weapons see this as solid (includes grates)
#define MASK_SHOT_HULL \
  (CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTER | CONTENTS_WINDOW | CONTENTS_DEBRIS | CONTENTS_GRATE)
// hits solids (not grates) and passes through everything else
#define MASK_SHOT_PORTAL     (CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_MONSTER)
// everything normally solid, except monsters (world+brush only)
#define MASK_SOLID_BRUSHONLY (CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_GRATE)
// everything normally solid for player movement, except monsters (world+brush only)
#define MASK_PLAYERSOLID_BRUSHONLY \
  (CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_PLAYERCLIP | CONTENTS_GRATE)
// everything normally solid for npc movement, except monsters (world+brush only)
#define MASK_NPCSOLID_BRUSHONLY \
  (CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_MONSTERCLIP | CONTENTS_GRATE)
// just the world, used for route rebuilding
#define MASK_NPCWORLDSTATIC  (CONTENTS_SOLID | CONTENTS_WINDOW | CONTENTS_MONSTERCLIP | CONTENTS_GRATE)
// These are things that can split areaportals
#define MASK_SPLITAREAPORTAL (CONTENTS_WATER | CONTENTS_SLIME)

// UNDONE: This is untested, any moving water
#define MASK_CURRENT                                                                        \
  (CONTENTS_CURRENT_0 | CONTENTS_CURRENT_90 | CONTENTS_CURRENT_180 | CONTENTS_CURRENT_270 | \
   CONTENTS_CURRENT_UP | CONTENTS_CURRENT_DOWN)

// everything that blocks corpse movement
// UNDONE: Not used yet / may be deleted
#define MASK_DEADSOLID (CONTENTS_SOLID | CONTENTS_PLAYERCLIP | CONTENTS_WINDOW | CONTENTS_GRATE)
