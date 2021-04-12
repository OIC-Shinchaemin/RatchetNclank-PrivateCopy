#pragma once
#include "Mof.h"
#include "MofImGui/MofImGui.h"
#include "Define.h"
#include "StageObjectCommandRegister.h"
#include "Singleton.h"

// ********************************************************************************
/// <summary>
/// �I�u�W�F�N�g���Ǘ�����E�B���h�E
/// </summary>
// ********************************************************************************
class ObjectWindow : public Singleton<ObjectWindow> {
private:

    //! �I�u�W�F�N�g���X�g
    std::vector<ObjectData>    _object_list;
    //! �I�𒆂̔ԍ�      
    int                        _object_list_current    { 0 };
    //! �I�𒆂̃A�C�e��       
    ObjectData*                _object_select_item     { nullptr };
    ObjectData                 _object_select_item_prev;
    //! �I�u�W�F�N�g�̃g�����X�t�H�[�������͕��@
    bool                       _object_data_input_mode { true };
    //! �I�u�W�F�N�g�̕ύX�t���O
    bool                       _object_change_flag     { false };
    //! �R�}���h
    StageObjectCommandRegister _command_register       { &_object_change_flag, _object_select_item };

    // ********************************************************************************
    /// <summary>
    /// �I�u�W�F�N�g���X�g�̕\��
    /// </summary>
    /// <created>���̂���,2021/03/20</created>
    /// <changed>���̂���,2021/03/20</changed>
    // ********************************************************************************
    void ShowObjectList(void);

    // ********************************************************************************
    /// <summary>
    /// �I�𒆂̃I�u�W�F�N�g�f�[�^����\��
    /// </summary>
    /// <created>���̂���,2021/03/20</created>
    /// <changed>���̂���,2021/03/20</changed>
    // ********************************************************************************
    void ShowObjectInfo(void);

public:

    // ********************************************************************************
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <created>���̂���,2021/03/20</created>
    /// <changed>���̂���,2021/03/20</changed>
    // ********************************************************************************
    ObjectWindow(void);
    
    // ********************************************************************************
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    /// <created>���̂���,2021/03/20</created>
    /// <changed>���̂���,2021/03/20</changed>
    // ********************************************************************************
    ~ObjectWindow(void);

    // ********************************************************************************
    /// <summary>
    /// �E�B���h�E�̕\��
    /// </summary>
    /// <created>���̂���,2021/03/20</created>
    /// <changed>���̂���,2021/03/20</changed>
    // ********************************************************************************
    void Show(void);

    // ********************************************************************************
    /// <summary>
    /// �I�u�W�F�N�g�f�[�^�̒ǉ�
    /// </summary>
    /// <param name="data">�ǉ�����f�[�^</param>
    /// <created>���̂���,2021/03/20</created>
    /// <changed>���̂���,2021/03/20</changed>
    // ********************************************************************************
    void Add(ObjectData& data);

    // ********************************************************************************
    /// <summary>
    /// �f�[�^�̔j��
    /// </summary>
    /// <created>���̂���,2021/03/20</created>
    /// <changed>���̂���,2021/03/20</changed>
    // ********************************************************************************
    void Remove(void);
    void Remove(const ObjectData& data);

    // ********************************************************************************
    /// <summary>
    /// ���ݑI�𒆂̃f�[�^���擾����
    /// </summary>
    /// <returns>���ݑI�𒆂̃f�[�^�|�C���^</returns>
    /// <created>���̂���,2021/03/20</created>
    /// <changed>���̂���,2021/03/20</changed>
    // ********************************************************************************
    ObjectData* GetSelectObjectData(void);

    // ********************************************************************************
    /// <summary>
    /// �I�u�W�F�N�g���X�g�̎擾
    /// </summary>
    /// <returns>�I�u�W�F�N�g���X�g</returns>
    /// <created>���̂���,2021/03/20</created>
    /// <changed>���̂���,2021/03/20</changed>
    // ********************************************************************************
    const std::vector<ObjectData>& GetObjectList(void) const;
    std::vector<ObjectData>& GetObjectList(void);

    // ********************************************************************************
    /// <summary>
    /// �I�𒆂̃I�u�W�F�N�g�ԍ��̎擾
    /// </summary>
    /// <returns>�I�𒆂̃I�u�W�F�N�g�ԍ�</returns>
    /// <created>���̂���,2021/04/08</created>
    /// <changed>���̂���,2021/04/08</changed>
    // ********************************************************************************
    int GetSelectNo(void) const;
};

