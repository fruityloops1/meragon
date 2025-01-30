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
TR("�N���b�s���O", "Clipping")
TR("�Z���T�[", "Sensor")
TR("�|�C���e�B���O", "Pointing")
TR("��", "Sky")
TR("���i�i�Œ�n�`�j", "Distant view (Fixed MapParts)")
TR("���i�i�f���m�o�b�j", "Distant view (demo NPC)")
TR("���i", "Vision")
TR("�Œ�n�`", "Fixed MapParts")
TR("�Œ�n�`�I�u�W�F", "Fixed MapParts object")
TR("�Œ�n�`[�L������]", "Fixed MapParts [after character]")
TR("�R���W�����n�`", "Collision terrain")
TR("�R���W�����n�`[Movement]", "Collision terrain [Movement]")
TR("�R���W�����n�`����", "Collision terrain decoration")
TR("�R���W�����n�`����[Movement]", "Collision terrain decoration [MOVEMENT]")
TR("�R���W�����n�`[�L������]", "Collision terrain [after character]")
TR("�R���W�����G", "Collision enemy")
TR("�R���W�����A�C�e��", "Collision item")
TR("�R���W�����f�B���N�^�[", "Collision director")
TR("���i", "MiddleView")
TR("�n�`�I�u�W�F", "Terrain object")
TR("�n�`�I�u�W�F[Movement]", "Terrain object [Movement]")
TR("�n�`�I�u�W�F[�L������]", "Terrain object [after the character]")
TR("�n�`�I�u�W�F[�e�Ȃ�]", "Terrain object [No shadow]")
TR("�n�`�I�u�W�F����", "Terrain object decoration")
TR("���[�v�I�u�W�F[�e�Ȃ�]", "Warp object [No shadow]")
TR("�f��", "demo")
TR("�f��[�e�Ȃ�]", "Demo [No shadow]")
TR("�f��[Movement]", "Demo [Movement]")
TR("�v���C���[[Movement]", "Player [Movement]") 
TR("�v���C���[", "Player")
TR("�v���C���[���f��", "Player model")
TR("�v���C���[����", "Player decoration")
TR("�v���C���[�����Q", "Player decoration 2")
TR("�S�[�X�g�v���C���[�L�^", "GhostPlayerRecorder")
TR("�G�O[Movement]", "In front of the enemy [movement]")
TR("�G", "enemy")
TR("�G[Movement]", "Enemy [Movement]")
TR("�G����", "Enemy decoration")
TR("�m�o�b", "�m�o�b")
TR("�A�C�e��", "item")
TR("�A�C�e������", "Item decoration")
TR("�A�C�e���X�g�b�N���f��", "Item stock model")
TR("�V���G�b�g���f��", "Silhouette model")
TR("�J�X�^���V���G�b�g", "Custom silhouette")
TR("�e[Movement]", "Shadow [Movement]")
TR("�e�{�����[��", "Shadow volume")
TR("�v���C���[�e�{�����[��", "Player shadow volume")
TR("�t�H�O�f�B���N�^�[", "Fog Director")
TR("�X�e�[�W�X�C�b�`�f�B���N�^�[", "Stage Switch Director")
TR("�J�����U��", "Camera Vibration")
TR("�Q�c", "�Q��")
TR("�Q�c�i�|�[�Y�����j", "2D (ignoring pose)")
TR("�G�t�F�N�g", "effect")
TR("�G�t�F�N�g�i�v���C���[�j", "Effect (player)")
TR("�G�t�F�N�g�i�x�[�X�Q�c�j", "Effect (base 2D)")
TR("�G�t�F�N�g�i�Q�c�j", "Effect (2D)")
TR("�G�t�F�N�g�i����ʃx�[�X�Q�c�j", "Effect (lower screen base 2D)")
TR("�G�t�F�N�g�i����ʂQ�c�j", "Effect (lower screen 2D)")
TR("��", "null")
TR("���i�i�Œ�n�`�j", "Vision (fixed terrain)")
TR("���i", "Vision")
TR("���i�i�f���m�o�b�j", "Distant view (demo NPC)")
TR("�Q�c�G���h���[���e�L�X�g", "2D end roll text")
TR("�Œ�n�`", "Fixed terrain")
TR("�Œ�n�`�I�u�W�F", "Fixed terrain object")
TR("�R���W�����n�`", "Collision terrain")
TR("�R���W�����n�`����", "Collision terrain decoration")
TR("�R���W�����G", "Collision enemy")
TR("�R���W�����A�C�e��", "Collision item")
TR("���i", "MiddleView")
TR("�n�`�I�u�W�F", "Terrain object")
TR("�n�`�I�u�W�F����", "Terrain object decoration")
TR("�J�X�^���V���G�b�g", "Custom silhouette")
TR("�f��", "demo")
TR("�e�{�����[��", "Shadow volume")
TR("�V���G�b�g���f��", "Silhouette model")
TR("�e�{�����[���̃t�B��", "Shadow volume fill")
TR("�V�F�[�_�[[Draw]�i�e�̌�j", "Shader [Draw] (after the shadow)")
TR("�G", "enemy")
TR("�G[Draw]", "Enemy [Draw]")
TR("�G����", "Enemy decoration")
TR("�m�o�b", "�m�o�b")
TR("�A�C�e��", "item")
TR("�A�C�e������", "Item decoration")
TR("�n�`�I�u�W�F[�e�Ȃ�]", "Terrain object [No shadow]")
TR("���[�v�I�u�W�F[�e�Ȃ�]", "Warp object [No shadow]")
TR("�v���C���[�e�{�����[��", "Player shadow volume")
TR("�v���C���[�e�{�����[���̃t�B��", "Player shadow volume Phil")
TR("�V�F�[�_�[[Draw]�i�v���C���[�e�̌�j", "Shader [Draw] (after the player shadow)")
TR("�v���C���[", "Player")
TR("�v���C���[���f��", "Player model")
TR("�v���C���[����", "Player decoration")
TR("�v���C���[�����Q", "Player decoration 2")
TR("�Œ�n�`[�L������]", "Fixed terrain [after character]")
TR("�R���W�����n�`[�L������]", "Collision terrain [after the character]")
TR("�n�`�I�u�W�F[�L������]", "Terrain object [after the character]")
TR("�f��[�e�Ȃ�]", "Demonstration [No shadow]")
TR("�Q�c�A�C�R��", "2D icon")
TR("�Q�c�x�[�X", "2D base")
TR("�Q�c�V�l�}�t���[��", "2D cinema frame")
TR("�Q�c", "�Q��")
TR("�Q�c�ʐ^", "2D photo")
TR("�Q�c�w�b�h", "2D head")
TR("�Q�c�|�[�Y", "2D pose")
TR("�Q�c�J�[�\��", "2D cursor")
TR("�Q�c�J�[�e��", "2D curtain")
TR("�Q�c�J�E���^�[", "2D counter")
TR("�Q�c�E�B���h�E", "2D window")
TR("�Q�c����K�C�h", "2D operation guide")
TR("�Q�c���C�v", "2D wipe")
TR("�Q�c�J�E���^�[[���C�v��]", "2D counter [after wipe]")
TR("�Q�c�Q�[���I�[�o�[", "2D game over")
TR("�Q�c�\�t�g���Z�b�g", "2D soft reset")
TR("�Q�c�x�[�X�i����ʁj", "2D base (lower screen)")
TR("�Q�c�i����ʁj", "2D (below)")
TR("�A�C�e���X�g�b�N���f��", "Item stock model")
TR("�Q�c�|�[�Y�i����ʁj", "2D pose (lower screen)")
TR("�Q�c�J�[�e���i����ʁj", "2D curtain (lower screen)")
TR("�Q�c�J�E���^�[�i����ʁj", "2D counter (lower screen)")
TR("�Q�c�Q�[���I�[�o�[�w�i�i����ʁj", "2D game over background (lower screen)")
TR("�Q�c�Q�[���I�[�o�[�i����ʁj", "2D game over (lower screen)")
TR("�Q�c�E�B���h�E�i����ʁj", "2D window (lower screen)")
TR("�Q�c�J�[�\���i����ʁj", "2D cursor (lower screen)")
TR("�Q�c���C�v�i����ʁj", "2D wipe (lower screen)")
TR("�Q�c�\�t�g���Z�b�g�i����ʁj", "2D soft reset (lower screen)")
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
