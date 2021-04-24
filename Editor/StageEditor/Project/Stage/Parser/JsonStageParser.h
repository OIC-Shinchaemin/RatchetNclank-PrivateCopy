#pragma once
#include "StageParser.h"
#include "My/Core/Utility.h"
#include "My/Core/Header.h"

/// <summary>
/// json�t�@�C������X�e�[�W�f�[�^�ɕ�������N���X
/// </summary>
class JsonStageParser : public IStageParser {
protected:

    bool MeshListParse(rapidjson::Document& json, MeshArray* out);
    bool StaticObjectListParse(rapidjson::Document& json, StageObjectArray* out);
    bool EnemySpawnListParse(rapidjson::Document& json, EnemySpawnArray* out);
    bool GimmickObjectListParse(rapidjson::Document& json, GimmickArray* out);

    GimmickPtr CreateGimmick(StageObjectType type, const rapidjson::Value& data);

public:

    /// <summary>
    /// �t�@�C������X�e�[�W�f�[�^�ɕ�������
    /// </summary>
    /// <param name="path">�t�@�C���p�X</param>
    /// <param name="out">�o�̓f�[�^</param>
    /// <returns>StageFileResult_Success : ����, ����ȊO : error</returns>
    virtual StageFileResult Load(const std::string& path, ParseData& out) override;
};

