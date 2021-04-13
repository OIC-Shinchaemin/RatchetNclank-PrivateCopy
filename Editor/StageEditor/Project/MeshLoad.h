#pragma once
#include "ActionBase.h"
#include <string>

// ********************************************************************************
/// <summary>
/// ���b�V���̓ǂݍ��݂��s���N���X
/// </summary>
// ********************************************************************************
class MeshLoad : public ActionBase {

public:
    using MeshLoadData = std::pair<std::string, std::string>;

    // ********************************************************************************
    /// <summary>
    /// �ǂݍ���
    /// </summary>
    /// <param name="mesh_load_data">�L�[�ƃt�@�C���p�X�̃y�A</param>
    /// <returns>true : �ǂݍ��ݐ���, false : ���s</returns>
    /// <created>���̂���,2021/03/18</created>
    /// <changed>���̂���,2021/03/18</changed>
    // ********************************************************************************
    virtual bool Action(std::any mesh_load_data) override;
};

