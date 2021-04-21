#pragma once
#include "StageParser.h"
#include "My/Core/Utility.h"
#include "My/Core/Header.h"

/// <summary>
/// jsonファイルからステージデータに分解するクラス
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
    /// ファイルからステージデータに分解する
    /// </summary>
    /// <param name="path">ファイルパス</param>
    /// <param name="out">出力データ</param>
    /// <returns>StageFileResult_Success : 成功, それ以外 : error</returns>
    virtual StageFileResult Load(const std::string& path, ParseData& out) override;
};

