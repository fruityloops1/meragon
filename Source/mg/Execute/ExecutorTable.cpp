#include "al/Execute/ExecuteOrder.h"
#include "al/Execute/ExecuteTableHolderDraw.h"
#include "al/Execute/ExecuteTableHolderUpdate.h"
#include "hk/hook/BranchHook.h"

namespace mg {

#define SIZEOF(THING) (sizeof(THING) / sizeof(THING[0]))

constexpr al::ExecuteOrder cUpdateTable[] {
    { "クリッピング", "Execute", 1, "システム" },
    { "センサー", "Execute", 1, "システム" },
    { "ポインティング", "Execute", 8, "システム" },
    { "空", "ActorMovementCalcAnim", 8, "地形" },
    { "遠景（固定地形）", "ActorMovementCalcAnim", 32, "地形" },
    { "遠景（デモＮＰＣ）", "ActorMovementCalcAnim", 16, "ＮＰＣ" },
    { "遠景", "ActorMovementCalcAnim", 8, "地形" },
    { "固定地形", "ActorMovementCalcAnim", 32, "地形" },
    { "固定地形オブジェ", "ActorMovementCalcAnim", 256, "地形オブジェ" },
    { "固定地形[キャラ後]", "ActorMovementCalcAnim", 32, "地形" },
    { "コリジョン地形", "ActorMovementCalcAnim", 128, "地形" },
    { "コリジョン地形[Movement]", "ActorMovement", 32, "地形" },
    { "コリジョン地形装飾", "ActorMovementCalcAnim", 32, "地形" },
    { "コリジョン地形装飾[Movement]", "ActorMovement", 32, "地形" },
    { "コリジョン地形[キャラ後]", "ActorMovementCalcAnim", 32, "地形" },
    { "コリジョン敵", "ActorMovementCalcAnim", 32, "敵" },
    { "コリジョンアイテム", "ActorMovementCalcAnim", 32, "アイテム" },
    { "コリジョンディレクター", "Execute", 1, "システム" },
    { "中景", "ActorMovementCalcAnim", 8, "地形" },
    { "地形オブジェ", "ActorMovementCalcAnim", 128, "地形オブジェ" },
    { "地形オブジェ[Movement]", "ActorMovement", 32, "地形オブジェ" },
    { "地形オブジェ[キャラ後]", "ActorMovementCalcAnim", 128, "地形オブジェ" },
    { "地形オブジェ[影なし]", "ActorMovementCalcAnim", 64, "地形オブジェ" },
    { "地形オブジェ装飾", "ActorMovementCalcAnim", 32, "地形オブジェ" },
    { "ワープオブジェ[影なし]", "ActorMovementCalcAnim", 32, "地形オブジェ" },
    { "デモ", "ActorMovementCalcAnim", 32, "地形オブジェ" },
    { "デモ[影なし]", "ActorMovementCalcAnim", 32, "地形オブジェ" },
    { "デモ[Movement]", "ActorMovement", 32, "地形オブジェ" },
    { "プレイヤー[Movement]", "ActorMovement", 1, "プレイヤー" },
    { "プレイヤー", "ActorMovementCalcAnim", 8, "プレイヤー" },
    { "プレイヤーモデル", "ActorMovementCalcAnim", 8, "プレイヤー" },
    { "プレイヤー装飾", "ActorMovementCalcAnim", 32, "プレイヤー" },
    { "プレイヤー装飾２", "ActorMovementCalcAnim", 8, "プレイヤー" },
    { "ゴーストプレイヤー記録", "Functor", 1, "敵" },
    { "敵前[Movement]", "ActorMovement", 32, "敵" },
    { "敵", "ActorMovementCalcAnim", 64, "敵" },
    { "敵[Movement]", "ActorMovement", 32, "敵" },
    { "敵装飾", "ActorMovementCalcAnim", 32, "敵" },
    { "ＮＰＣ", "ActorMovementCalcAnim", 32, "ＮＰＣ" },
    { "アイテム", "ActorMovementCalcAnim", 64, "アイテム" },
    { "アイテム装飾", "ActorMovementCalcAnim", 32, "アイテム" },
    { "アイテムストックモデル", "ActorMovementCalcAnim", 32, "アイテム" },
    { "シルエットモデル", "ActorMovementCalcAnim", 16, "影" },
    { "カスタムシルエット", "ActorMovementCalcAnim", 8, "影" },
    { "影[Movement]", "ActorMovement", 8, "影" },
    { "影ボリューム", "ActorMovementCalcAnim", 32, "影" },
    { "プレイヤー影ボリューム", "ActorMovementCalcAnim", 8, "影" },
    { "フォグディレクター", "Execute", 1, "システム" },
    { "ステージスイッチディレクター", "Execute", 1, "システム" },
    { "カメラ振動", "Functor", 1, "システム" },
    { "２Ｄ", "LayoutUpdate", 256, "レイアウト" },
    { "２Ｄ（ポーズ無視）", "LayoutUpdate", 64, "レイアウト" },
    { "エフェクト", "Execute", 1, "エフェクト" },
    { "エフェクト（プレイヤー）", "Execute", 1, "エフェクト" },
    { "エフェクト（ベース２Ｄ）", "Execute", 1, "エフェクト" },
    { "エフェクト（２Ｄ）", "Execute", 1, "エフェクト" },
    { "エフェクト（下画面ベース２Ｄ）", "Execute", 1, "エフェクト" },
    { "エフェクト（下画面２Ｄ）", "Execute", 1, "エフェクト" },
};

constexpr al::ExecuteOrder cDrawTable1[] {
    { "空", "ActorModelDraw", 8, "地形" },
    { "遠景（固定地形）", "ActorModelDrawModelCache", 32, "地形" },
    { "遠景", "ActorModelDraw", 8, "地形" },
    { "遠景（デモＮＰＣ）", "ActorModelDraw", 16, "ＮＰＣ" },
};

constexpr al::ExecuteOrder cDrawTable2[] {
    { "２Ｄエンドロールテキスト", "LayoutDraw", 64, "レイアウト" },
};

constexpr al::ExecuteOrder cDrawTable3[] {
    { "固定地形", "ActorModelDrawModelCache", 32, "地形" },
    { "固定地形オブジェ", "ActorModelDrawModelCache", 256, "地形オブジェ" },
};

constexpr al::ExecuteOrder cDrawTable4[] {
    { "コリジョン地形", "ActorModelDraw", 128, "地形" },
    { "コリジョン地形装飾", "ActorModelDraw", 32, "地形" },
    { "コリジョン敵", "ActorModelDraw", 32, "敵" },
    { "コリジョンアイテム", "ActorModelDraw", 32, "アイテム" },
    { "中景", "ActorModelDraw", 8, "地形" },
    { "地形オブジェ", "ActorModelDraw", 128, "地形オブジェ" },
    { "地形オブジェ装飾", "ActorModelDraw", 32, "地形オブジェ" },
    { "カスタムシルエット", "ActorModelDraw", 8, "地形オブジェ" },
    { "デモ", "ActorModelDraw", 32, "地形オブジェ" },
    { "影ボリューム", "ActorModelDraw", 32, "影" },
    { "シルエットモデル", "ActorModelDraw", 16, "影" },
    { "影ボリュームのフィル", "Functor", 1, "影" },
    { "シェーダー[Draw]（影の後）", "Draw", 1, "システム" },
    { "敵", "ActorModelDraw", 128, "敵" },
    { "敵[Draw]", "ActorModelDraw", 8, "敵" },
    { "敵装飾", "ActorModelDraw", 32, "敵" },
    { "ＮＰＣ", "ActorModelDraw", 32, "ＮＰＣ" },
    { "アイテム", "ActorModelDraw", 32, "アイテム" },
    { "アイテム装飾", "ActorModelDraw", 32, "アイテム" },
    { "地形オブジェ[影なし]", "ActorModelDraw", 64, "地形オブジェ" },
    { "ワープオブジェ[影なし]", "ActorModelDraw", 32, "地形オブジェ" },
    { "プレイヤー影ボリューム", "ActorModelDraw", 8, "影" },
    { "プレイヤー影ボリュームのフィル", "Functor", 1, "影" },
    { "シェーダー[Draw]（プレイヤー影の後）", "Draw", 1, "システム" },
    { "プレイヤー", "ActorModelDraw", 8, "プレイヤー" },
    { "プレイヤーモデル", "ActorModelDraw", 8, "プレイヤー" },
    { "プレイヤー装飾", "ActorModelDraw", 32, "プレイヤー" },
    { "プレイヤー装飾２", "ActorModelDraw", 8, "プレイヤー" },
    { "固定地形[キャラ後]", "ActorModelDrawModelCache", 32, "地形" },
    { "コリジョン地形[キャラ後]", "ActorModelDraw", 8, "地形" },
    { "地形オブジェ[キャラ後]", "ActorModelDraw", 128, "地形オブジェ" },
    { "デモ[影なし]", "ActorModelDraw", 32, "地形オブジェ" },
};

constexpr al::ExecuteOrder cDrawTable5[] {
    { "２Ｄアイコン", "LayoutDraw", 64, "レイアウト" },
};

constexpr al::ExecuteOrder cDrawTable6[] {
    { "２Ｄベース", "LayoutDraw", 64, "レイアウト" },
    { "２Ｄシネマフレーム", "LayoutDraw", 8, "レイアウト" },
    { "２Ｄ", "LayoutDraw", 128, "レイアウト" },
    { "２Ｄ写真", "LayoutDraw", 32, "レイアウト" },
    { "２Ｄヘッド", "LayoutDraw", 32, "レイアウト" },
};

constexpr al::ExecuteOrder cDrawTable7[] {
    { "２Ｄポーズ", "LayoutDraw", 8, "レイアウト" },
    { "２Ｄカーソル", "LayoutDraw", 8, "レイアウト" },
    { "２Ｄカーテン", "LayoutDraw", 8, "レイアウト" },
    { "２Ｄカウンター", "LayoutDraw", 16, "レイアウト" },
    { "２Ｄウィンドウ", "LayoutDraw", 16, "レイアウト" },
    { "２Ｄ操作ガイド", "LayoutDraw", 4, "レイアウト" },
    { "２Ｄワイプ", "LayoutDraw", 16, "レイアウト" },
    { "２Ｄカウンター[ワイプ後]", "LayoutDraw", 8, "レイアウト" },
    { "２Ｄゲームオーバー", "LayoutDraw", 8, "レイアウト" },
    { "２Ｄソフトリセット", "LayoutDraw", 1, "レイアウト" },
};

constexpr al::ExecuteOrder cDrawTable8[] {
    { "２Ｄベース（下画面）", "LayoutDrawBottom", 8, "レイアウト" },
    { "２Ｄ（下画面）", "LayoutDrawBottom", 32, "レイアウト" },
};
constexpr al::ExecuteOrder cDrawTable9[] {
    { "アイテムストックモデル", "ActorModelDraw", 32, "アイテム" },
};
constexpr al::ExecuteOrder cDrawTable10[] {
    { "２Ｄポーズ（下画面）", "LayoutDrawBottom", 8, "レイアウト" },
    { "２Ｄカーテン（下画面）", "LayoutDrawBottom", 16, "レイアウト" },
    { "２Ｄカウンター（下画面）", "LayoutDrawBottom", 16, "レイアウト" },
    { "２Ｄゲームオーバー背景（下画面）", "LayoutDrawBottom", 8, "レイアウト" },
    { "２Ｄゲームオーバー（下画面）", "LayoutDrawBottom", 8, "レイアウト" },
    { "２Ｄウィンドウ（下画面）", "LayoutDrawBottom", 32, "レイアウト" },
    { "２Ｄカーソル（下画面）", "LayoutDrawBottom", 16, "レイアウト" },
    { "２Ｄワイプ（下画面）", "LayoutDrawBottom", 16, "レイアウト" },
    { "２Ｄソフトリセット（下画面）", "LayoutDrawBottom", 1, "レイアウト" },
};

static void initUpdateTable(al::ExecuteTableHolderUpdate* table, const al::ExecuteOrder* order, int numOrder)
{
    table->init(cUpdateTable, SIZEOF(cUpdateTable));
}

static void initDrawTable1(al::ExecuteTableHolderDraw* table, const al::ExecuteOrder* order, int numOrder) { table->init("３Ｄ（空）", cDrawTable1, SIZEOF(cDrawTable1)); }
static void initDrawTable2(al::ExecuteTableHolderDraw* table, const al::ExecuteOrder* order, int numOrder) { table->init("２Ｄエンドロールテキスト（上画面）", cDrawTable2, SIZEOF(cDrawTable2)); }
static void initDrawTable3(al::ExecuteTableHolderDraw* table, const al::ExecuteOrder* order, int numOrder) { table->init("３Ｄ（固定地形）", cDrawTable3, SIZEOF(cDrawTable3)); }
static void initDrawTable4(al::ExecuteTableHolderDraw* table, const al::ExecuteOrder* order, int numOrder) { table->init("３Ｄ（上画面）", cDrawTable4, SIZEOF(cDrawTable4)); }
static void initDrawTable5(al::ExecuteTableHolderDraw* table, const al::ExecuteOrder* order, int numOrder) { table->init("２Ｄアイコン（上画面）", cDrawTable5, SIZEOF(cDrawTable5)); }
static void initDrawTable6(al::ExecuteTableHolderDraw* table, const al::ExecuteOrder* order, int numOrder) { table->init("２Ｄベース（上画面）", cDrawTable6, SIZEOF(cDrawTable6)); }
static void initDrawTable7(al::ExecuteTableHolderDraw* table, const al::ExecuteOrder* order, int numOrder) { table->init("２Ｄ（上画面）", cDrawTable7, SIZEOF(cDrawTable7)); }
static void initDrawTable8(al::ExecuteTableHolderDraw* table, const al::ExecuteOrder* order, int numOrder) { table->init("２Ｄベース（下画面）", cDrawTable8, SIZEOF(cDrawTable8)); }
static void initDrawTable9(al::ExecuteTableHolderDraw* table, const al::ExecuteOrder* order, int numOrder) { table->init("３Ｄ（アイテムストック）", cDrawTable9, SIZEOF(cDrawTable9)); }
static void initDrawTable10(al::ExecuteTableHolderDraw* table, const al::ExecuteOrder* order, int numOrder) { table->init("２Ｄ（下画面）", cDrawTable10, SIZEOF(cDrawTable10)); }

HK_BL_HOOK_FUNC(InitExecuteTableUpdate, 0x001ccabc, initUpdateTable)

HK_BL_HOOK_FUNC(InitExecuteTableDraw1, 0x001ccb40, initDrawTable1)
HK_BL_HOOK_FUNC(InitExecuteTableDraw2, 0x001ccb58, initDrawTable2)
HK_BL_HOOK_FUNC(InitExecuteTableDraw3, 0x001ccb70, initDrawTable3)
HK_BL_HOOK_FUNC(InitExecuteTableDraw4, 0x001ccb88, initDrawTable4)
HK_BL_HOOK_FUNC(InitExecuteTableDraw5, 0x001ccba0, initDrawTable5)
HK_BL_HOOK_FUNC(InitExecuteTableDraw6, 0x001ccbb8, initDrawTable6)
HK_BL_HOOK_FUNC(InitExecuteTableDraw7, 0x001ccbd0, initDrawTable7)
HK_BL_HOOK_FUNC(InitExecuteTableDraw8, 0x001ccbe8, initDrawTable8)
HK_BL_HOOK_FUNC(InitExecuteTableDraw9, 0x001ccc00, initDrawTable9)
HK_BL_HOOK_FUNC(InitExecuteTableDraw10, 0x001ccc18, initDrawTable10)

} // namespace mg
