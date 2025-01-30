#include "mg/Util/StringTranslation.h"
#include "al/Math/HashUtil.h"

namespace mg {

struct TranslateEntry {
    u32 hash;
    const char* translated;
};

#define TR(ORIG, TRANSLATED) { al::calcHashCode(ORIG), TRANSLATED },

constexpr TranslateEntry cEntries[] {
    // clang-format off
TR("クリッピング", "Clipping")
TR("センサー", "Sensor")
TR("ポインティング", "Pointing")
TR("空", "Sky")
TR("遠景（固定地形）", "Distant view (Fixed MapParts)")
TR("遠景（デモＮＰＣ）", "Distant view (demo NPC)")
TR("遠景", "Vision")
TR("固定地形", "Fixed MapParts")
TR("固定地形オブジェ", "Fixed MapParts object")
TR("固定地形[キャラ後]", "Fixed MapParts [after character]")
TR("コリジョン地形", "Collision terrain")
TR("コリジョン地形[Movement]", "Collision terrain [Movement]")
TR("コリジョン地形装飾", "Collision terrain decoration")
TR("コリジョン地形装飾[Movement]", "Collision terrain decoration [MOVEMENT]")
TR("コリジョン地形[キャラ後]", "Collision terrain [after character]")
TR("コリジョン敵", "Collision enemy")
TR("コリジョンアイテム", "Collision item")
TR("コリジョンディレクター", "Collision director")
TR("中景", "MiddleView")
TR("地形オブジェ", "Terrain object")
TR("地形オブジェ[Movement]", "Terrain object [Movement]")
TR("地形オブジェ[キャラ後]", "Terrain object [after the character]")
TR("地形オブジェ[影なし]", "Terrain object [No shadow]")
TR("地形オブジェ装飾", "Terrain object decoration")
TR("ワープオブジェ[影なし]", "Warp object [No shadow]")
TR("デモ", "demo")
TR("デモ[影なし]", "Demo [No shadow]")
TR("デモ[Movement]", "Demo [Movement]")
TR("プレイヤー[Movement]", "Player [Movement]") 
TR("プレイヤー", "Player")
TR("プレイヤーモデル", "Player model")
TR("プレイヤー装飾", "Player decoration")
TR("プレイヤー装飾２", "Player decoration 2")
TR("ゴーストプレイヤー記録", "GhostPlayerRecorder")
TR("敵前[Movement]", "In front of the enemy [movement]")
TR("敵", "enemy")
TR("敵[Movement]", "Enemy [Movement]")
TR("敵装飾", "Enemy decoration")
TR("ＮＰＣ", "ＮＰＣ")
TR("アイテム", "item")
TR("アイテム装飾", "Item decoration")
TR("アイテムストックモデル", "Item stock model")
TR("シルエットモデル", "Silhouette model")
TR("カスタムシルエット", "Custom silhouette")
TR("影[Movement]", "Shadow [Movement]")
TR("影ボリューム", "Shadow volume")
TR("プレイヤー影ボリューム", "Player shadow volume")
TR("フォグディレクター", "Fog Director")
TR("ステージスイッチディレクター", "Stage Switch Director")
TR("カメラ振動", "Camera Vibration")
TR("２Ｄ", "２ｄ")
TR("２Ｄ（ポーズ無視）", "2D (ignoring pose)")
TR("エフェクト", "effect")
TR("エフェクト（プレイヤー）", "Effect (player)")
TR("エフェクト（ベース２Ｄ）", "Effect (base 2D)")
TR("エフェクト（２Ｄ）", "Effect (2D)")
TR("エフェクト（下画面ベース２Ｄ）", "Effect (lower screen base 2D)")
TR("エフェクト（下画面２Ｄ）", "Effect (lower screen 2D)")
TR("空", "null")
TR("遠景（固定地形）", "Vision (fixed terrain)")
TR("遠景", "Vision")
TR("遠景（デモＮＰＣ）", "Distant view (demo NPC)")
TR("２Ｄエンドロールテキスト", "2D end roll text")
TR("固定地形", "Fixed terrain")
TR("固定地形オブジェ", "Fixed terrain object")
TR("コリジョン地形", "Collision terrain")
TR("コリジョン地形装飾", "Collision terrain decoration")
TR("コリジョン敵", "Collision enemy")
TR("コリジョンアイテム", "Collision item")
TR("中景", "MiddleView")
TR("地形オブジェ", "Terrain object")
TR("地形オブジェ装飾", "Terrain object decoration")
TR("カスタムシルエット", "Custom silhouette")
TR("デモ", "demo")
TR("影ボリューム", "Shadow volume")
TR("シルエットモデル", "Silhouette model")
TR("影ボリュームのフィル", "Shadow volume fill")
TR("シェーダー[Draw]（影の後）", "Shader [Draw] (after the shadow)")
TR("敵", "enemy")
TR("敵[Draw]", "Enemy [Draw]")
TR("敵装飾", "Enemy decoration")
TR("ＮＰＣ", "ＮＰＣ")
TR("アイテム", "item")
TR("アイテム装飾", "Item decoration")
TR("地形オブジェ[影なし]", "Terrain object [No shadow]")
TR("ワープオブジェ[影なし]", "Warp object [No shadow]")
TR("プレイヤー影ボリューム", "Player shadow volume")
TR("プレイヤー影ボリュームのフィル", "Player shadow volume Phil")
TR("シェーダー[Draw]（プレイヤー影の後）", "Shader [Draw] (after the player shadow)")
TR("プレイヤー", "Player")
TR("プレイヤーモデル", "Player model")
TR("プレイヤー装飾", "Player decoration")
TR("プレイヤー装飾２", "Player decoration 2")
TR("固定地形[キャラ後]", "Fixed terrain [after character]")
TR("コリジョン地形[キャラ後]", "Collision terrain [after the character]")
TR("地形オブジェ[キャラ後]", "Terrain object [after the character]")
TR("デモ[影なし]", "Demonstration [No shadow]")
TR("２Ｄアイコン", "2D icon")
TR("２Ｄベース", "2D base")
TR("２Ｄシネマフレーム", "2D cinema frame")
TR("２Ｄ", "２ｄ")
TR("２Ｄ写真", "2D photo")
TR("２Ｄヘッド", "2D head")
TR("２Ｄポーズ", "2D pose")
TR("２Ｄカーソル", "2D cursor")
TR("２Ｄカーテン", "2D curtain")
TR("２Ｄカウンター", "2D counter")
TR("２Ｄウィンドウ", "2D window")
TR("２Ｄ操作ガイド", "2D operation guide")
TR("２Ｄワイプ", "2D wipe")
TR("２Ｄカウンター[ワイプ後]", "2D counter [after wipe]")
TR("２Ｄゲームオーバー", "2D game over")
TR("２Ｄソフトリセット", "2D soft reset")
TR("２Ｄベース（下画面）", "2D base (lower screen)")
TR("２Ｄ（下画面）", "2D (below)")
TR("アイテムストックモデル", "Item stock model")
TR("２Ｄポーズ（下画面）", "2D pose (lower screen)")
TR("２Ｄカーテン（下画面）", "2D curtain (lower screen)")
TR("２Ｄカウンター（下画面）", "2D counter (lower screen)")
TR("２Ｄゲームオーバー背景（下画面）", "2D game over background (lower screen)")
TR("２Ｄゲームオーバー（下画面）", "2D game over (lower screen)")
TR("２Ｄウィンドウ（下画面）", "2D window (lower screen)")
TR("２Ｄカーソル（下画面）", "2D cursor (lower screen)")
TR("２Ｄワイプ（下画面）", "2D wipe (lower screen)")
TR("２Ｄソフトリセット（下画面）", "2D soft reset (lower screen)")
//clang-format on
    };

template <size_t N>
struct Entries 
{
    TranslateEntry e[N];

    constexpr static size_t size = N;
};

template <size_t N>
constexpr Entries<N> sortEntries(const TranslateEntry(&entries)[N])
{
    Entries<N> result;
    for (size_t i = 0; i < N; ++i)
    {
        result.e[i] = entries[i];
        for (size_t j = i; j > 0 && result.e[j].hash < result.e[j - 1].hash; --j)
        {
            TranslateEntry temp = result.e[j];
            result.e[j] = result.e[j - 1];
            result.e[j - 1] = temp;

        }
    }
    return result;
}

constexpr auto cSorted = sortEntries(cEntries);

const char* tryTranslateString(const char* str)
{
    u32 hash = al::calcHashCode(str);
    // binary search
    size_t left = 0;
    size_t right = cSorted.size - 1;

    while (left <= right) {
        size_t mid = left + (right - left) / 2;

        if (cSorted.e[mid].hash == hash) {
            return cSorted.e[mid].translated;
        }

        if (cSorted.e[mid].hash < hash) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return nullptr;
}

} // namespace mg
