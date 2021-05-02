#pragma once
#include "Stage.h"
#include "StageFileFormat.h"

#include <memory>
#include <string>

/// <summary>
/// 分解後出力データ構造体
/// </summary>
struct ParseData {
    MeshArray*        mesh_array_pointer;
    StageObjectArray* static_object_array_pointer;
    EnemySpawnArray*  enemy_spawn_array_pointer;
    GimmickArray*     gimmick_array_pointer;
    WoodBoxArray*     box_array_pointer;
};

/// <summary>
/// ステージデータ分解インターフェース
/// </summary>
class IStageParser {
public:

    /// <summary>
    /// ファイルからステージデータに分解する
    /// </summary>
    /// <param name="path">ファイルパス</param>
    /// <param name="out">出力データ</param>
    /// <returns>StageFileResult_Success : 成功, それ以外 : error</returns>
    virtual StageFileResult Load(const std::string& path, ParseData& out) = 0;
};

// ポインタ置き換え
using StageParserPtr = std::shared_ptr<IStageParser>;