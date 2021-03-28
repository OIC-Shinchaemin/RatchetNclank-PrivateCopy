#pragma once
#include "ActionBase.h"
#include <string>

// ********************************************************************************
/// <summary>
/// メッシュの読み込みを行うクラス
/// </summary>
// ********************************************************************************
class MeshLoad : public ActionBase {

public:
    using MeshLoadData = std::pair<std::string, std::string>;

    // ********************************************************************************
    /// <summary>
    /// 読み込み
    /// </summary>
    /// <param name="mesh_load_data">キーとファイルパスのペア</param>
    /// <returns>true : 読み込み成功, false : 失敗</returns>
    /// <created>いのうえ,2021/03/18</created>
    /// <changed>いのうえ,2021/03/18</changed>
    // ********************************************************************************
    virtual bool Action(std::any mesh_load_data) override;
};

