#pragma once
#include "Stage.h"
#include "StageFileFormat.h"

#include <memory>
#include <string>

/// <summary>
/// ������o�̓f�[�^�\����
/// </summary>
struct ParseData {
    MeshArray*        mesh_array_pointer;
    StageObjectArray* static_object_array_pointer;
    EnemySpawnArray*  enemy_spawn_array_pointer;
    GimmickArray*     gimmick_array_pointer;
    WoodBoxArray*     box_array_pointer;
};

/// <summary>
/// �X�e�[�W�f�[�^�����C���^�[�t�F�[�X
/// </summary>
class IStageParser {
public:

    /// <summary>
    /// �t�@�C������X�e�[�W�f�[�^�ɕ�������
    /// </summary>
    /// <param name="path">�t�@�C���p�X</param>
    /// <param name="out">�o�̓f�[�^</param>
    /// <returns>StageFileResult_Success : ����, ����ȊO : error</returns>
    virtual StageFileResult Load(const std::string& path, ParseData& out) = 0;
};

// �|�C���^�u������
using StageParserPtr = std::shared_ptr<IStageParser>;