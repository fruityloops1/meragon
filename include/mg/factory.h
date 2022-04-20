#pragma once

#include "al/actor/liveactor.h"
#include "al/factory.h"
#include "mg/actors/gabon.h"

class Kinopio;
class Luigi;
class Peach;
class PeachForTitle;
class BlockDragonGenerator;
class BombHei;
class BombHeiGenerator;
class BombHeiTail;
class BombHeiTailGenerator;
class BoomerangBros;
class Bubble;
class Bug;
class Chorobon;
class ChorobonGenerator;
class Choropu;
class Dossun;
class DossunTail;
class EnemyCounter;
class Fugumannen;
class FugumannenGenerator;
class GamaguchiKun;
class Gesso;
class GhostPlayer;
class HammerBros;
class Hoppun;
class Indy;
class Kameck;
class Karon;
class Killer;
class KillerGenerator;
class KillerMagnum;
class Kuribo;
class KuriboTail;
class KuriboTailSearch;
class KuriboTower;
class Meragon;
class Nokonoko;
class PackunFire;
class PackunFlower;
class PackunInk;
class PataKuribo;
class Poo;
class Pukupuku;
class PukupukuGenerator;
class PukupukuLoopRail;
class SamboBody;
class SamboHead;
class Sokuten;
class TentenGenerator;
class Teresa;
class TeresaGroup;
class TeresaRail;
class TogeMetbo;
class Togezo;
class Utsubo;
class Wanwan;
class WooGan;
class WooGanSand;
class Bunbun;
class BunbunAndPunpunTagObj;
class BunbunMysteryBox;
class Koopa;
class Punpun;
class PunpunStageDamageFire;
class BoomerangFlower;
class Coin;
class CoinBox;
class CoinCollect;
class CoinGathering;
class CoinGenerator;
class CoinRailGenerator;
class CoinRailMoveGenerator;
class CoinRedStarter;
class CoinRing;
class FireFlower;
class KickKoura;
class KinokoOneUp;
class KinokoOneUpFast;
class KinokoPoison;
class KinokoPoisonFast;
class KinokoSuper;
class KinokoSuperFast;
class PatapataWing;
class PropellerBlock;
class SuperLeaf;
class SuperLeafSpecial;
class SuperStar;
class Telescope;
class TelescopeTarget;
class TimerClock;
class AppearStep;
class AquariumSwimDebris;
class BalanceTruck;
class BeatBlock;
class BeatBlockHolder;
class Bird;
class BlindCloud;
class BlockBrick;
class BlockBrickItem;
class BlockEmpty;
class BlockHelp;
class BlockNote;
class BlockNoteSuper;
class BlockQuestion;
class BlockQuestionFlying;
class BlockQuestionLong;
class BlockRailCurve;
class BlockRailStraight;
class BlockRailTerminater;
class BlockRoulette;
class BlockTransparent;
class BoneRollerCoaster;
class BridgePukupukuBreakBridge;
class Burner;
class Candlestand;
class CandlestandFire;
class CandlestandObserver;
class CourseSelectObj;
class EntranceCameraObj;
class FallStone;
class FireBarCore;
class FrameOutChecker;
class Garigari;
class GeneratorBox;
class GeneratorBoxHop;
class GeneratorBoxHopChild;
class GeneratorEnemy;
class GoAndReturnParts;
class Gorori;
class GororiGenerator;
class Grass;
class GrassMike;
class GroundRiserAttachment;
class GyroLauncher;
class JumpFlipBoard;
class Kabehei;
class KeyMoveAndFallParts;
class KickStone;
class KickStoneStrong;
class KoopaCollapseStep;
class KoopaDoor;
class KoopaDoorLast;
class KoopaFireGenerator;
class KoopaPillar;
class KoopaSwitch;
class LavaConveyer;
class LavaGeyser;
class LiftGeyser;
class LiftGeyserStep;
class MarinePlant;
class NeedleBar;
class NeedleBarCore;
class NeedleBlock;
class NeedleFloor;
class NeedlePlant;
class NeedleRoller;
class NeedleTrap;
class NutLift;
class PatanBoard;
class PatanBoardStarter;
class PatanBox;
class PeraObj;
class PhotoAlbum;
class Picket;
class Plant;
class Pole;
class PresentBox;
class RailDotDrawer;
class RestartObj;
class Rope;
class ShadowObj;
class SpikeStick;
class StickNeedle;
class SwingNeedleRoller;
class SwingSpike;
class TrampleSwitch;
class Trampoline;
class TransparentWall;
class TreeA;
class TrickHintPanel;
class Trilift;
class UpperBlock;
class WarpLift;
class WoodBox;
class Seagull;
class SoundEmitObj;
class NoteObj;
class NoteObjGenerator;
class WarpAreaPoint;
class WarpCube;
class WarpPorter;
class Dokan;
class WarpDoor;
class AttackRevolvingPanel;
class ClockMapParts;
class CollapseBreakMapParts;
class CollapseMapParts;
class FallMapParts;
class FixMapParts;
class FloaterMapParts;
class KeyMoveMapParts;
class RailMoveMapParts;
class RollingReflectMapParts;
class RollingShakeMapParts;
class RotateMapParts;
class SeesawMapParts;
class SlideMapParts;
class SwingLift;
class SwingMapParts;
class SwitchRotateMapParts;
class SwitchSlideMapParts;
class VisibleSwitchMapParts;
class WheelMapParts;
class WobbleMapParts;
class Sky;
class EffectObj;
class EffectObjFollowCamera;
class EffectObjLiftLiner;
class EffectObjReEmit;
class EffectObjSensor;
class EffectObjStream;
class EffectObjSwitch;
class WaterFlowCube;
class StreetPassObj;
class DemoStarter;

#include "sead/heap/seadNew.h"

inline void* operator new(size_t, void* inst)
{
    return inst;
} // no clue this is stupid

namespace mg {

template <typename T>
al::LiveActor* createActorFunction(const char* name)
{
    al::LiveActor* actor = (T*)opNew(sizeof(T));
    new (actor) T(name);
    return actor;
}

constexpr const al::NameToCreatorActor actorTable[] {
    { "Kinopio", al::createActorFunction<Kinopio> },
    { "Luigi", al::createActorFunction<Luigi> },
    { "Peach", al::createActorFunction<Peach> },
    { "PeachForTitle", al::createActorFunction<PeachForTitle> },
    { "BlockDragonGenerator", al::createActorFunction<BlockDragonGenerator> },
    { "BombHei", al::createActorFunction<BombHei> },
    { "BombHeiGenerator", al::createActorFunction<BombHeiGenerator> },
    { "BombHeiTail", al::createActorFunction<BombHeiTail> },
    { "BombHeiTailGenerator", al::createActorFunction<BombHeiTailGenerator> },
    { "BoomerangBros", al::createActorFunction<BoomerangBros> },
    { "Bubble", al::createActorFunction<Bubble> },
    { "Bug", al::createActorFunction<Bug> },
    { "Chorobon", al::createActorFunction<Chorobon> },
    { "ChorobonGenerator", al::createActorFunction<ChorobonGenerator> },
    { "Choropu", al::createActorFunction<Choropu> },
    { "Dossun", al::createActorFunction<Dossun> },
    { "DossunTail", al::createActorFunction<DossunTail> },
    { "EnemyCounter", al::createActorFunction<EnemyCounter> },
    { "Fugumannen", al::createActorFunction<Fugumannen> },
    { "FugumannenGenerator", al::createActorFunction<FugumannenGenerator> },
    { "GamaguchiKun", al::createActorFunction<GamaguchiKun> },
    { "Gesso", al::createActorFunction<Gesso> },
    { "GhostPlayer", al::createActorFunction<GhostPlayer> },
    { "HammerBros", al::createActorFunction<HammerBros> },
    { "Hoppun", al::createActorFunction<Hoppun> },
    { "Indy", al::createActorFunction<Indy> },
    { "Kameck", al::createActorFunction<Kameck> },
    { "Karon", al::createActorFunction<Karon> },
    { "Killer", al::createActorFunction<Killer> },
    { "KillerGenerator", al::createActorFunction<KillerGenerator> },
    { "KillerMagnum", al::createActorFunction<KillerMagnum> },
    { "Kuribo", mg::createActorFunction<mg::Gabon> },
    { "KuriboTail", al::createActorFunction<KuriboTail> },
    { "KuriboTailSearch", al::createActorFunction<KuriboTailSearch> },
    { "KuriboTower", al::createActorFunction<KuriboTower> },
    { "Meragon", al::createActorFunction<Meragon> },
    { "Nokonoko", al::createActorFunction<Nokonoko> },
    { "PackunFire", al::createActorFunction<PackunFire> },
    { "PackunFlower", al::createActorFunction<PackunFlower> },
    { "PackunInk", al::createActorFunction<PackunInk> },
    { "PataKuribo", al::createActorFunction<PataKuribo> },
    { "Poo", al::createActorFunction<Poo> },
    { "Pukupuku", al::createActorFunction<Pukupuku> },
    { "PukupukuGenerator", al::createActorFunction<PukupukuGenerator> },
    { "PukupukuLoopRail", al::createActorFunction<PukupukuLoopRail> },
    { "SamboBody", al::createActorFunction<SamboBody> },
    { "SamboHead", al::createActorFunction<SamboHead> },
    { "Sokuten", al::createActorFunction<Sokuten> },
    { "TentenGenerator", al::createActorFunction<TentenGenerator> },
    { "Teresa", al::createActorFunction<Teresa> },
    { "TeresaGroup", al::createActorFunction<TeresaGroup> },
    { "TeresaRail", al::createActorFunction<TeresaRail> },
    { "TogeMetbo", al::createActorFunction<TogeMetbo> },
    { "Togezo", al::createActorFunction<Togezo> },
    { "Utsubo", al::createActorFunction<Utsubo> },
    { "Wanwan", al::createActorFunction<Wanwan> },
    { "WooGan", al::createActorFunction<WooGan> },
    { "WooGanSand", al::createActorFunction<WooGanSand> },
    { "Bunbun", al::createActorFunction<Bunbun> },
    { "BunbunAndPunpunTagObj", al::createActorFunction<BunbunAndPunpunTagObj> },
    { "BunbunMysteryBox", al::createActorFunction<BunbunMysteryBox> },
    { "Koopa", al::createActorFunction<Koopa> },
    { "Punpun", al::createActorFunction<Punpun> },
    { "PunpunStageDamageFire", al::createActorFunction<PunpunStageDamageFire> },
    { "BoomerangFlower", al::createActorFunction<BoomerangFlower> },
    { "Coin", al::createActorFunction<Coin> },
    { "CoinBox", al::createActorFunction<CoinBox> },
    { "CoinCollect", al::createActorFunction<CoinCollect> },
    { "CoinGathering", al::createActorFunction<CoinGathering> },
    { "CoinGenerator", al::createActorFunction<CoinGenerator> },
    { "CoinRailGenerator", al::createActorFunction<CoinRailGenerator> },
    { "CoinRailMoveGenerator", al::createActorFunction<CoinRailMoveGenerator> },
    { "CoinRedStarter", al::createActorFunction<CoinRedStarter> },
    { "CoinRing", al::createActorFunction<CoinRing> },
    { "FireFlower", al::createActorFunction<FireFlower> },
    { "KickKoura", al::createActorFunction<KickKoura> },
    { "KinokoOneUp", al::createActorFunction<KinokoOneUp> },
    { "KinokoOneUpFast", al::createActorFunction<KinokoOneUpFast> },
    { "KinokoPoison", al::createActorFunction<KinokoPoison> },
    { "KinokoPoisonFast", al::createActorFunction<KinokoPoisonFast> },
    { "KinokoSuper", al::createActorFunction<KinokoSuper> },
    { "KinokoSuperFast", al::createActorFunction<KinokoSuperFast> },
    { "PatapataWing", al::createActorFunction<PatapataWing> },
    { "PropellerBlock", al::createActorFunction<PropellerBlock> },
    { "SuperLeaf", al::createActorFunction<SuperLeaf> },
    { "SuperLeafSpecial", al::createActorFunction<SuperLeafSpecial> },
    { "SuperStar", al::createActorFunction<SuperStar> },
    { "Telescope", al::createActorFunction<Telescope> },
    { "TelescopeTarget", al::createActorFunction<TelescopeTarget> },
    { "TimerClock", al::createActorFunction<TimerClock> },
    { "AppearStep", al::createActorFunction<AppearStep> },
    { "AquariumSwimDebris", al::createActorFunction<AquariumSwimDebris> },
    { "BalanceTruck", al::createActorFunction<BalanceTruck> },
    { "BeatBlock", al::createActorFunction<BeatBlock> },
    { "BeatBlockHolder", al::createActorFunction<BeatBlockHolder> },
    { "Bird", al::createActorFunction<Bird> },
    { "BlindCloud", al::createActorFunction<BlindCloud> },
    { "BlockBrick", al::createActorFunction<BlockBrick> },
    { "BlockBrickItem", al::createActorFunction<BlockBrickItem> },
    { "BlockEmpty", al::createActorFunction<BlockEmpty> },
    { "BlockHelp", al::createActorFunction<BlockHelp> },
    { "BlockNote", al::createActorFunction<BlockNote> },
    { "BlockNoteSuper", al::createActorFunction<BlockNoteSuper> },
    { "BlockQuestion", al::createActorFunction<BlockQuestion> },
    { "BlockQuestionFlying", al::createActorFunction<BlockQuestionFlying> },
    { "BlockQuestionLong", al::createActorFunction<BlockQuestionLong> },
    { "BlockRailCurve", al::createActorFunction<BlockRailCurve> },
    { "BlockRailStraight", al::createActorFunction<BlockRailStraight> },
    { "BlockRailTerminater", al::createActorFunction<BlockRailTerminater> },
    { "BlockRoulette", al::createActorFunction<BlockRoulette> },
    { "BlockTransparent", al::createActorFunction<BlockTransparent> },
    { "BoneRollerCoaster", al::createActorFunction<BoneRollerCoaster> },
    { "BridgePukupukuBreakBridge", al::createActorFunction<BridgePukupukuBreakBridge> },
    { "Burner", al::createActorFunction<Burner> },
    { "Candlestand", al::createActorFunction<Candlestand> },
    { "CandlestandFire", al::createActorFunction<CandlestandFire> },
    { "CandlestandObserver", al::createActorFunction<CandlestandObserver> },
    { "CourseSelectObj", al::createActorFunction<CourseSelectObj> },
    { "EntranceCameraObj", al::createActorFunction<EntranceCameraObj> },
    { "FallStone", al::createActorFunction<FallStone> },
    { "FireBarCore", al::createActorFunction<FireBarCore> },
    { "FrameOutChecker", al::createActorFunction<FrameOutChecker> },
    { "Garigari", al::createActorFunction<Garigari> },
    { "GeneratorBox", al::createActorFunction<GeneratorBox> },
    { "GeneratorBoxHop", al::createActorFunction<GeneratorBoxHop> },
    { "GeneratorBoxHopChild", al::createActorFunction<GeneratorBoxHopChild> },
    { "GeneratorEnemy", al::createActorFunction<GeneratorEnemy> },
    { "GoAndReturnParts", al::createActorFunction<GoAndReturnParts> },
    { "Gorori", al::createActorFunction<Gorori> },
    { "GororiGenerator", al::createActorFunction<GororiGenerator> },
    { "Grass", al::createActorFunction<Grass> },
    { "GrassMike", al::createActorFunction<GrassMike> },
    { "GroundRiserAttachment", al::createActorFunction<GroundRiserAttachment> },
    { "GyroLauncher", al::createActorFunction<GyroLauncher> },
    { "JumpFlipBoard", al::createActorFunction<JumpFlipBoard> },
    { "Kabehei", al::createActorFunction<Kabehei> },
    { "KeyMoveAndFallParts", al::createActorFunction<KeyMoveAndFallParts> },
    { "KickStone", al::createActorFunction<KickStone> },
    { "KickStoneStrong", al::createActorFunction<KickStoneStrong> },
    { "KoopaCollapseStep", al::createActorFunction<KoopaCollapseStep> },
    { "KoopaDoor", al::createActorFunction<KoopaDoor> },
    { "KoopaDoorLast", al::createActorFunction<KoopaDoorLast> },
    { "KoopaFireGenerator", al::createActorFunction<KoopaFireGenerator> },
    { "KoopaPillar", al::createActorFunction<KoopaPillar> },
    { "KoopaSwitch", al::createActorFunction<KoopaSwitch> },
    { "LavaConveyer", al::createActorFunction<LavaConveyer> },
    { "LavaGeyser", al::createActorFunction<LavaGeyser> },
    { "LiftGeyser", al::createActorFunction<LiftGeyser> },
    { "LiftGeyserStep", al::createActorFunction<LiftGeyserStep> },
    { "MarinePlant", al::createActorFunction<MarinePlant> },
    { "NeedleBar", al::createActorFunction<NeedleBar> },
    { "NeedleBarCore", al::createActorFunction<NeedleBarCore> },
    { "NeedleBlock", al::createActorFunction<NeedleBlock> },
    { "NeedleFloor", al::createActorFunction<NeedleFloor> },
    { "NeedlePlant", al::createActorFunction<NeedlePlant> },
    { "NeedleRoller", al::createActorFunction<NeedleRoller> },
    { "NeedleTrap", al::createActorFunction<NeedleTrap> },
    { "NutLift", al::createActorFunction<NutLift> },
    { "PatanBoard", al::createActorFunction<PatanBoard> },
    { "PatanBoardStarter", al::createActorFunction<PatanBoardStarter> },
    { "PatanBox", al::createActorFunction<PatanBox> },
    { "PeraObj", al::createActorFunction<PeraObj> },
    { "PhotoAlbum", al::createActorFunction<PhotoAlbum> },
    { "Picket", al::createActorFunction<Picket> },
    { "Plant", al::createActorFunction<Plant> },
    { "Pole", al::createActorFunction<Pole> },
    { "PresentBox", al::createActorFunction<PresentBox> },
    { "RailDotDrawer", al::createActorFunction<RailDotDrawer> },
    { "RestartObj", al::createActorFunction<RestartObj> },
    { "Rope", al::createActorFunction<Rope> },
    { "ShadowObj", al::createActorFunction<ShadowObj> },
    { "SpikeStick", al::createActorFunction<SpikeStick> },
    { "StickNeedle", al::createActorFunction<StickNeedle> },
    { "SwingNeedleRoller", al::createActorFunction<SwingNeedleRoller> },
    { "SwingSpike", al::createActorFunction<SwingSpike> },
    { "TrampleSwitch", al::createActorFunction<TrampleSwitch> },
    { "Trampoline", al::createActorFunction<Trampoline> },
    { "TransparentWall", al::createActorFunction<TransparentWall> },
    { "TreeA", al::createActorFunction<TreeA> },
    { "TrickHintPanel", al::createActorFunction<TrickHintPanel> },
    { "Trilift", al::createActorFunction<Trilift> },
    { "UpperBlock", al::createActorFunction<UpperBlock> },
    { "WarpLift", al::createActorFunction<WarpLift> },
    { "WoodBox", al::createActorFunction<WoodBox> },
    { "Seagull", al::createActorFunction<Seagull> },
    { "SoundEmitObj", al::createActorFunction<SoundEmitObj> },
    { "NoteObj", al::createActorFunction<NoteObj> },
    { "NoteObjGenerator", al::createActorFunction<NoteObjGenerator> },
    { "WarpAreaPoint", al::createActorFunction<WarpAreaPoint> },
    { "WarpCube", al::createActorFunction<WarpCube> },
    { "WarpPorter", al::createActorFunction<WarpPorter> },
    { "Dokan", al::createActorFunction<Dokan> },
    { "WarpDoor", al::createActorFunction<WarpDoor> },
    { "AttackRevolvingPanel", al::createActorFunction<AttackRevolvingPanel> },
    { "ClockMapParts", al::createActorFunction<ClockMapParts> },
    { "CollapseBreakMapParts", al::createActorFunction<CollapseBreakMapParts> },
    { "CollapseMapParts", al::createActorFunction<CollapseMapParts> },
    { "FallMapParts", al::createActorFunction<FallMapParts> },
    { "FixMapParts", al::createActorFunction<FixMapParts> },
    { "FloaterMapParts", al::createActorFunction<FloaterMapParts> },
    { "KeyMoveMapParts", al::createActorFunction<KeyMoveMapParts> },
    { "RailMoveMapParts", al::createActorFunction<RailMoveMapParts> },
    { "RollingReflectMapParts", al::createActorFunction<RollingReflectMapParts> },
    { "RollingShakeMapParts", al::createActorFunction<RollingShakeMapParts> },
    { "RotateMapParts", al::createActorFunction<RotateMapParts> },
    { "SeesawMapParts", al::createActorFunction<SeesawMapParts> },
    { "SlideMapParts", al::createActorFunction<SlideMapParts> },
    { "SwingLift", al::createActorFunction<SwingLift> },
    { "SwingMapParts", al::createActorFunction<SwingMapParts> },
    { "SwitchRotateMapParts", al::createActorFunction<SwitchRotateMapParts> },
    { "SwitchSlideMapParts", al::createActorFunction<SwitchSlideMapParts> },
    { "VisibleSwitchMapParts", al::createActorFunction<VisibleSwitchMapParts> },
    { "WheelMapParts", al::createActorFunction<WheelMapParts> },
    { "WobbleMapParts", al::createActorFunction<WobbleMapParts> },
    { "Sky", al::createActorFunction<Sky> },
    { "EffectObj", al::createActorFunction<EffectObj> },
    { "EffectObjFollowCamera", al::createActorFunction<EffectObjFollowCamera> },
    { "EffectObjLiftLiner", al::createActorFunction<EffectObjLiftLiner> },
    { "EffectObjReEmit", al::createActorFunction<EffectObjReEmit> },
    { "EffectObjSensor", al::createActorFunction<EffectObjSensor> },
    { "EffectObjStream", al::createActorFunction<EffectObjStream> },
    { "EffectObjSwitch", al::createActorFunction<EffectObjSwitch> },
    { "WaterFlowCube", al::createActorFunction<WaterFlowCube> },
    { "StreetPassObj", al::createActorFunction<StreetPassObj> },
    { "DemoStarter", al::createActorFunction<DemoStarter> },
    { "Gabon", mg::createActorFunction<mg::Gabon> }
};

constexpr const u8 actorTableEntryAmount = sizeof(mg::actorTable) / sizeof(mg::actorTable[0]);

} // namespace mg
