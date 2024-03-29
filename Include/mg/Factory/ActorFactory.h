#pragma once

#include "al/Factory/ActorFactory.h"

// Actor stubs

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
class WaterFlowCube;
class StreetPassObj;
class DemoStarter;

namespace al {

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

} // namespace al

const extern al::NameToActorCreator sActorFactoryEntries[225];

#include "al/Factory/ActorFactory.h"
#include "sead/basis/seadNew.h"
// #include <type_traits>

namespace mg {

template <typename T>
al::LiveActor* createActorFunction(const char* name)
{
    // static_assert(std::is_base_of<al::LiveActor, T>::value, "T must derive from al::LiveActor");
    return new T(name);
}

al::CreateActorFuncPtr getActorCreatorFromFactory(const char* className);

} // namespace mg
