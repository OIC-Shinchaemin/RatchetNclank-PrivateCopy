#pragma once
#include <Mof.h>

#include <string>
#include <memory>

#include "StageDefine.h"

// ���O�̒u������
using MeshPtr   = std::shared_ptr<CMeshContainer>;
using MeshArray = std::vector<MeshPtr>;

/// <summary>
/// �X�e�[�W�I�u�W�F�N�g�N���X
/// </summary>
class StageObject : public std::enable_shared_from_this<StageObject> {
protected:

    //! �I�u�W�F�N�g�̗L���t���O
    bool             _enable;

    //! �����蔻��̗L���t���O
    bool             _collision_enable;

    //! �I�u�W�F�N�g�̎��
    StageObjectType  _type;

    //! �I�u�W�F�N�g�̖��O
    std::string      _name;

    //! ���b�V���z��̉��Ԗڂ��g�p���Ă��邩
    int              _mesh_no;

    //! ���[���h���W
    Vector3          _position;
    
    //! �g��
    Vector3          _scale;

    //! ��]
    Vector3          _rotate;

    //! �`��p���[���h�}�g���N�X
    CMatrix44        _world_matrix;

public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    StageObject(bool enable = true, bool collision = true,
        StageObjectType type = StageObjectType::None, std::string name = "",
        int mesh_no = -1,
        Vector3 pos = Vector3(),
        Vector3 scale = Vector3(1, 1, 1),
        Vector3 rotate = Vector3());
    
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~StageObject(void);

    /// <summary>
    /// �L���t���O�̎擾
    /// </summary>
    /// <returns>�L���t���O</returns>
    bool IsEnable(void) const;

    /// <summary>
    /// �����蔻��t���O�̎擾
    /// </summary>
    /// <returns>�����蔻��t���O</returns>
    bool IsCollisionEnable(void) const;

    /// <summary>
    /// ��ނ̎擾
    /// </summary>
    /// <returns>���</returns>
    StageObjectType GetType(void) const;

    /// <summary>
    /// ���O�̎擾
    /// </summary>
    /// <returns>���O</returns>
    std::string GetName(void) const;

    /// <summary>
    /// ���b�V���ԍ��̎擾
    /// </summary>
    /// <returns>���b�V���ԍ�</returns>
    int GetMeshNo(void) const;

    /// <summary>
    /// ���W�̎擾
    /// </summary>
    /// <returns>���W</returns>
    Vector3 GetPosition(void) const;

    /// <summary>
    /// �g��̎擾
    /// </summary>
    /// <returns>�g��</returns>
    Vector3 GetScale(void) const;

    /// <summary>
    /// ��]�̎擾
    /// </summary>
    /// <returns>��]</returns>
    Vector3 GetRotate(void) const;

    /// <summary>
    /// ���[���h�}�g���N�X�̎擾
    /// </summary>
    /// <returns>���[���h�}�g���N�X</returns>
    CMatrix44 GetWorldMatrix(void) const;

    /// <summary>
    /// �`��p�}�g���N�X�̍Čv�Z
    /// </summary>
    void RefreshWorldMatrix(void);

    void SetEnable(bool b);
};

// �u������
using StageObjectPtr   = std::shared_ptr<StageObject>;
using StageObjectArray = std::vector<StageObjectPtr>;