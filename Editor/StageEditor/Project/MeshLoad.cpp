#include "MeshLoad.h"
#include "AssetBase.h"
#include "Define.h"

#include <filesystem>

// ********************************************************************************
/// <summary>
/// �ǂݍ���
/// </summary>
/// <param name="mesh_load_data">�L�[�ƃt�@�C���p�X�̃y�A</param>
/// <returns>true : �ǂݍ��ݐ���, false : ���s</returns>
/// <created>���̂���,2021/03/18</created>
/// <changed>���̂���,2021/03/18</changed>
// ********************************************************************************
bool MeshLoad::Action(std::any mesh_load_data) {
    MeshLoadData data = std::any_cast<MeshLoadData>(mesh_load_data);
    if (MeshAsset::GetAsset(data.first)) {
        MeshAsset::Erase(data.first);
    }
    return MeshAsset::Load(data.first, data.second.c_str());
}
