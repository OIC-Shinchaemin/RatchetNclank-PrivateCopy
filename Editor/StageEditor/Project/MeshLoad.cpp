#include "MeshLoad.h"
#include "AssetBase.h"
#include "Define.h"

#include <filesystem>

// ********************************************************************************
/// <summary>
/// 読み込み
/// </summary>
/// <param name="mesh_load_data">キーとファイルパスのペア</param>
/// <returns>true : 読み込み成功, false : 失敗</returns>
/// <created>いのうえ,2021/03/18</created>
/// <changed>いのうえ,2021/03/18</changed>
// ********************************************************************************
bool MeshLoad::Action(std::any mesh_load_data) {
    MeshLoadData data = std::any_cast<MeshLoadData>(mesh_load_data);
    if (MeshAsset::GetAsset(data.first)) {
        MeshAsset::Erase(data.first);
    }
    return MeshAsset::Load(data.first, data.second.c_str());
}
