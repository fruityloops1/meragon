#include "al/Execute/ExecuteOrder.h"
#include "al/Execute/ExecuteTableHolderDraw.h"
#include "al/Execute/ExecuteTableHolderUpdate.h"
#include "hk/hook/BranchHook.h"

namespace mg {

#define SIZEOF(THING) (sizeof(THING) / sizeof(THING[0]))

constexpr al::ExecuteOrder cUpdateTable[] {
    { "�N���b�s���O", "Execute", 1, "�V�X�e��" },
    { "�Z���T�[", "Execute", 1, "�V�X�e��" },
    { "�|�C���e�B���O", "Execute", 8, "�V�X�e��" },
    { "��", "ActorMovementCalcAnim", 8, "�n�`" },
    { "���i�i�Œ�n�`�j", "ActorMovementCalcAnim", 32, "�n�`" },
    { "���i�i�f���m�o�b�j", "ActorMovementCalcAnim", 16, "�m�o�b" },
    { "���i", "ActorMovementCalcAnim", 8, "�n�`" },
    { "�Œ�n�`", "ActorMovementCalcAnim", 32, "�n�`" },
    { "�Œ�n�`�I�u�W�F", "ActorMovementCalcAnim", 256, "�n�`�I�u�W�F" },
    { "�Œ�n�`[�L������]", "ActorMovementCalcAnim", 32, "�n�`" },
    { "�R���W�����n�`", "ActorMovementCalcAnim", 128, "�n�`" },
    { "�R���W�����n�`[Movement]", "ActorMovement", 32, "�n�`" },
    { "�R���W�����n�`����", "ActorMovementCalcAnim", 32, "�n�`" },
    { "�R���W�����n�`����[Movement]", "ActorMovement", 32, "�n�`" },
    { "�R���W�����n�`[�L������]", "ActorMovementCalcAnim", 32, "�n�`" },
    { "�R���W�����G", "ActorMovementCalcAnim", 32, "�G" },
    { "�R���W�����A�C�e��", "ActorMovementCalcAnim", 32, "�A�C�e��" },
    { "�R���W�����f�B���N�^�[", "Execute", 1, "�V�X�e��" },
    { "���i", "ActorMovementCalcAnim", 8, "�n�`" },
    { "�n�`�I�u�W�F", "ActorMovementCalcAnim", 128, "�n�`�I�u�W�F" },
    { "�n�`�I�u�W�F[Movement]", "ActorMovement", 32, "�n�`�I�u�W�F" },
    { "�n�`�I�u�W�F[�L������]", "ActorMovementCalcAnim", 128, "�n�`�I�u�W�F" },
    { "�n�`�I�u�W�F[�e�Ȃ�]", "ActorMovementCalcAnim", 64, "�n�`�I�u�W�F" },
    { "�n�`�I�u�W�F����", "ActorMovementCalcAnim", 32, "�n�`�I�u�W�F" },
    { "���[�v�I�u�W�F[�e�Ȃ�]", "ActorMovementCalcAnim", 32, "�n�`�I�u�W�F" },
    { "�f��", "ActorMovementCalcAnim", 32, "�n�`�I�u�W�F" },
    { "�f��[�e�Ȃ�]", "ActorMovementCalcAnim", 32, "�n�`�I�u�W�F" },
    { "�f��[Movement]", "ActorMovement", 32, "�n�`�I�u�W�F" },
    { "�v���C���[[Movement]", "ActorMovement", 1, "�v���C���[" },
    { "�v���C���[", "ActorMovementCalcAnim", 8, "�v���C���[" },
    { "�v���C���[���f��", "ActorMovementCalcAnim", 8, "�v���C���[" },
    { "�v���C���[����", "ActorMovementCalcAnim", 32, "�v���C���[" },
    { "�v���C���[�����Q", "ActorMovementCalcAnim", 8, "�v���C���[" },
    { "�S�[�X�g�v���C���[�L�^", "Functor", 1, "�G" },
    { "�G�O[Movement]", "ActorMovement", 32, "�G" },
    { "�G", "ActorMovementCalcAnim", 64, "�G" },
    { "�G[Movement]", "ActorMovement", 32, "�G" },
    { "�G����", "ActorMovementCalcAnim", 32, "�G" },
    { "�m�o�b", "ActorMovementCalcAnim", 32, "�m�o�b" },
    { "�A�C�e��", "ActorMovementCalcAnim", 64, "�A�C�e��" },
    { "�A�C�e������", "ActorMovementCalcAnim", 32, "�A�C�e��" },
    { "�A�C�e���X�g�b�N���f��", "ActorMovementCalcAnim", 32, "�A�C�e��" },
    { "�V���G�b�g���f��", "ActorMovementCalcAnim", 16, "�e" },
    { "�J�X�^���V���G�b�g", "ActorMovementCalcAnim", 8, "�e" },
    { "�e[Movement]", "ActorMovement", 8, "�e" },
    { "�e�{�����[��", "ActorMovementCalcAnim", 32, "�e" },
    { "�v���C���[�e�{�����[��", "ActorMovementCalcAnim", 8, "�e" },
    { "�t�H�O�f�B���N�^�[", "Execute", 1, "�V�X�e��" },
    { "�X�e�[�W�X�C�b�`�f�B���N�^�[", "Execute", 1, "�V�X�e��" },
    { "�J�����U��", "Functor", 1, "�V�X�e��" },
    { "�Q�c", "LayoutUpdate", 256, "���C�A�E�g" },
    { "�Q�c�i�|�[�Y�����j", "LayoutUpdate", 64, "���C�A�E�g" },
    { "�G�t�F�N�g", "Execute", 1, "�G�t�F�N�g" },
    { "�G�t�F�N�g�i�v���C���[�j", "Execute", 1, "�G�t�F�N�g" },
    { "�G�t�F�N�g�i�x�[�X�Q�c�j", "Execute", 1, "�G�t�F�N�g" },
    { "�G�t�F�N�g�i�Q�c�j", "Execute", 1, "�G�t�F�N�g" },
    { "�G�t�F�N�g�i����ʃx�[�X�Q�c�j", "Execute", 1, "�G�t�F�N�g" },
    { "�G�t�F�N�g�i����ʂQ�c�j", "Execute", 1, "�G�t�F�N�g" },
};

constexpr al::ExecuteOrder cDrawTable1[] {
    { "��", "ActorModelDraw", 8, "�n�`" },
    { "���i�i�Œ�n�`�j", "ActorModelDrawModelCache", 32, "�n�`" },
    { "���i", "ActorModelDraw", 8, "�n�`" },
    { "���i�i�f���m�o�b�j", "ActorModelDraw", 16, "�m�o�b" },
};

constexpr al::ExecuteOrder cDrawTable2[] {
    { "�Q�c�G���h���[���e�L�X�g", "LayoutDraw", 64, "���C�A�E�g" },
};

constexpr al::ExecuteOrder cDrawTable3[] {
    { "�Œ�n�`", "ActorModelDrawModelCache", 32, "�n�`" },
    { "�Œ�n�`�I�u�W�F", "ActorModelDrawModelCache", 256, "�n�`�I�u�W�F" },
};

constexpr al::ExecuteOrder cDrawTable4[] {
    { "�R���W�����n�`", "ActorModelDraw", 128, "�n�`" },
    { "�R���W�����n�`����", "ActorModelDraw", 32, "�n�`" },
    { "�R���W�����G", "ActorModelDraw", 32, "�G" },
    { "�R���W�����A�C�e��", "ActorModelDraw", 32, "�A�C�e��" },
    { "���i", "ActorModelDraw", 8, "�n�`" },
    { "�n�`�I�u�W�F", "ActorModelDraw", 128, "�n�`�I�u�W�F" },
    { "�n�`�I�u�W�F����", "ActorModelDraw", 32, "�n�`�I�u�W�F" },
    { "�J�X�^���V���G�b�g", "ActorModelDraw", 8, "�n�`�I�u�W�F" },
    { "�f��", "ActorModelDraw", 32, "�n�`�I�u�W�F" },
    { "�e�{�����[��", "ActorModelDraw", 32, "�e" },
    { "�V���G�b�g���f��", "ActorModelDraw", 16, "�e" },
    { "�e�{�����[���̃t�B��", "Functor", 1, "�e" },
    { "�V�F�[�_�[[Draw]�i�e�̌�j", "Draw", 1, "�V�X�e��" },
    { "�G", "ActorModelDraw", 128, "�G" },
    { "�G[Draw]", "ActorModelDraw", 8, "�G" },
    { "�G����", "ActorModelDraw", 32, "�G" },
    { "�m�o�b", "ActorModelDraw", 32, "�m�o�b" },
    { "�A�C�e��", "ActorModelDraw", 32, "�A�C�e��" },
    { "�A�C�e������", "ActorModelDraw", 32, "�A�C�e��" },
    { "�n�`�I�u�W�F[�e�Ȃ�]", "ActorModelDraw", 64, "�n�`�I�u�W�F" },
    { "���[�v�I�u�W�F[�e�Ȃ�]", "ActorModelDraw", 32, "�n�`�I�u�W�F" },
    { "�v���C���[�e�{�����[��", "ActorModelDraw", 8, "�e" },
    { "�v���C���[�e�{�����[���̃t�B��", "Functor", 1, "�e" },
    { "�V�F�[�_�[[Draw]�i�v���C���[�e�̌�j", "Draw", 1, "�V�X�e��" },
    { "�v���C���[", "ActorModelDraw", 8, "�v���C���[" },
    { "�v���C���[���f��", "ActorModelDraw", 8, "�v���C���[" },
    { "�v���C���[����", "ActorModelDraw", 32, "�v���C���[" },
    { "�v���C���[�����Q", "ActorModelDraw", 8, "�v���C���[" },
    { "�Œ�n�`[�L������]", "ActorModelDrawModelCache", 32, "�n�`" },
    { "�R���W�����n�`[�L������]", "ActorModelDraw", 8, "�n�`" },
    { "�n�`�I�u�W�F[�L������]", "ActorModelDraw", 128, "�n�`�I�u�W�F" },
    { "�f��[�e�Ȃ�]", "ActorModelDraw", 32, "�n�`�I�u�W�F" },
};

constexpr al::ExecuteOrder cDrawTable5[] {
    { "�Q�c�A�C�R��", "LayoutDraw", 64, "���C�A�E�g" },
};

constexpr al::ExecuteOrder cDrawTable6[] {
    { "�Q�c�x�[�X", "LayoutDraw", 64, "���C�A�E�g" },
    { "�Q�c�V�l�}�t���[��", "LayoutDraw", 8, "���C�A�E�g" },
    { "�Q�c", "LayoutDraw", 128, "���C�A�E�g" },
    { "�Q�c�ʐ^", "LayoutDraw", 32, "���C�A�E�g" },
    { "�Q�c�w�b�h", "LayoutDraw", 32, "���C�A�E�g" },
};

constexpr al::ExecuteOrder cDrawTable7[] {
    { "�Q�c�|�[�Y", "LayoutDraw", 8, "���C�A�E�g" },
    { "�Q�c�J�[�\��", "LayoutDraw", 8, "���C�A�E�g" },
    { "�Q�c�J�[�e��", "LayoutDraw", 8, "���C�A�E�g" },
    { "�Q�c�J�E���^�[", "LayoutDraw", 16, "���C�A�E�g" },
    { "�Q�c�E�B���h�E", "LayoutDraw", 16, "���C�A�E�g" },
    { "�Q�c����K�C�h", "LayoutDraw", 4, "���C�A�E�g" },
    { "�Q�c���C�v", "LayoutDraw", 16, "���C�A�E�g" },
    { "�Q�c�J�E���^�[[���C�v��]", "LayoutDraw", 8, "���C�A�E�g" },
    { "�Q�c�Q�[���I�[�o�[", "LayoutDraw", 8, "���C�A�E�g" },
    { "�Q�c�\�t�g���Z�b�g", "LayoutDraw", 1, "���C�A�E�g" },
};

constexpr al::ExecuteOrder cDrawTable8[] {
    { "�Q�c�x�[�X�i����ʁj", "LayoutDrawBottom", 8, "���C�A�E�g" },
    { "�Q�c�i����ʁj", "LayoutDrawBottom", 32, "���C�A�E�g" },
};
constexpr al::ExecuteOrder cDrawTable9[] {
    { "�A�C�e���X�g�b�N���f��", "ActorModelDraw", 32, "�A�C�e��" },
};
constexpr al::ExecuteOrder cDrawTable10[] {
    { "�Q�c�|�[�Y�i����ʁj", "LayoutDrawBottom", 8, "���C�A�E�g" },
    { "�Q�c�J�[�e���i����ʁj", "LayoutDrawBottom", 16, "���C�A�E�g" },
    { "�Q�c�J�E���^�[�i����ʁj", "LayoutDrawBottom", 16, "���C�A�E�g" },
    { "�Q�c�Q�[���I�[�o�[�w�i�i����ʁj", "LayoutDrawBottom", 8, "���C�A�E�g" },
    { "�Q�c�Q�[���I�[�o�[�i����ʁj", "LayoutDrawBottom", 8, "���C�A�E�g" },
    { "�Q�c�E�B���h�E�i����ʁj", "LayoutDrawBottom", 32, "���C�A�E�g" },
    { "�Q�c�J�[�\���i����ʁj", "LayoutDrawBottom", 16, "���C�A�E�g" },
    { "�Q�c���C�v�i����ʁj", "LayoutDrawBottom", 16, "���C�A�E�g" },
    { "�Q�c�\�t�g���Z�b�g�i����ʁj", "LayoutDrawBottom", 1, "���C�A�E�g" },
};

static void initUpdateTable(al::ExecuteTableHolderUpdate* table, const al::ExecuteOrder* order, int numOrder)
{
    table->init(cUpdateTable, SIZEOF(cUpdateTable));
}

static void initDrawTable1(al::ExecuteTableHolderDraw* table, const al::ExecuteOrder* order, int numOrder) { table->init("�R�c�i��j", cDrawTable1, SIZEOF(cDrawTable1)); }
static void initDrawTable2(al::ExecuteTableHolderDraw* table, const al::ExecuteOrder* order, int numOrder) { table->init("�Q�c�G���h���[���e�L�X�g�i���ʁj", cDrawTable2, SIZEOF(cDrawTable2)); }
static void initDrawTable3(al::ExecuteTableHolderDraw* table, const al::ExecuteOrder* order, int numOrder) { table->init("�R�c�i�Œ�n�`�j", cDrawTable3, SIZEOF(cDrawTable3)); }
static void initDrawTable4(al::ExecuteTableHolderDraw* table, const al::ExecuteOrder* order, int numOrder) { table->init("�R�c�i���ʁj", cDrawTable4, SIZEOF(cDrawTable4)); }
static void initDrawTable5(al::ExecuteTableHolderDraw* table, const al::ExecuteOrder* order, int numOrder) { table->init("�Q�c�A�C�R���i���ʁj", cDrawTable5, SIZEOF(cDrawTable5)); }
static void initDrawTable6(al::ExecuteTableHolderDraw* table, const al::ExecuteOrder* order, int numOrder) { table->init("�Q�c�x�[�X�i���ʁj", cDrawTable6, SIZEOF(cDrawTable6)); }
static void initDrawTable7(al::ExecuteTableHolderDraw* table, const al::ExecuteOrder* order, int numOrder) { table->init("�Q�c�i���ʁj", cDrawTable7, SIZEOF(cDrawTable7)); }
static void initDrawTable8(al::ExecuteTableHolderDraw* table, const al::ExecuteOrder* order, int numOrder) { table->init("�Q�c�x�[�X�i����ʁj", cDrawTable8, SIZEOF(cDrawTable8)); }
static void initDrawTable9(al::ExecuteTableHolderDraw* table, const al::ExecuteOrder* order, int numOrder) { table->init("�R�c�i�A�C�e���X�g�b�N�j", cDrawTable9, SIZEOF(cDrawTable9)); }
static void initDrawTable10(al::ExecuteTableHolderDraw* table, const al::ExecuteOrder* order, int numOrder) { table->init("�Q�c�i����ʁj", cDrawTable10, SIZEOF(cDrawTable10)); }

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
