#pragma once
#include "StageParser.h"

/// <summary>
/// jsonファイルからステージデータに分解するクラス
/// </summary>
class JsonStageParser : public IStageParser {
public:

    /// <summary>
    /// ファイルからステージデータに分解する
    /// </summary>
    /// <param name="path">ファイルパス</param>
    /// <param name="out">出力データ</param>
    /// <returns>StageFileResult_Success : 成功, それ以外 : error</returns>
    virtual StageFileResult Load(const std::string& path, ParseData& out) override;
};

