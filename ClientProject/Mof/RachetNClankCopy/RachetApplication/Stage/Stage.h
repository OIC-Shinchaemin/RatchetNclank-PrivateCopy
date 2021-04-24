#pragma once
#include "StageObject.h"
#include "GimmickBase.h"

// ���O�̒u������
using MeshPtr         = std::shared_ptr<CMeshContainer>;
using MeshArray       = std::vector<MeshPtr>;
// pair<builder_path, pos_data>
using EnemySpawnData  = std::pair<std::string, StageObjectPtr>;
using EnemySpawnArray = std::vector<EnemySpawnData>;

/// <summary>
/// �X�e�[�W�N���X
/// </summary>
class Stage {
private:

    //! �ÓI�ȃX�e�[�W���b�V���̐����t���O
    bool                _create_static_stage_mesh;

    //! �������̈ꎞ���b�V���u����(��������̂��ߕۑ�)
    CMeshContainerArray _copy_tmp_array;

    //! �X�e�[�W�Ŏg�p���郁�b�V���̔z��
    MeshArray           _mesh_array;

    //! �ÓI�ȃI�u�W�F�N�g�̔z��
    StageObjectArray    _static_object_array;

    //! �G�̏o���ʒu�z��
    EnemySpawnArray     _enemy_spawn_array;

    //! �M�~�b�N�̔z��
    GimmickArray        _gimmick_array;

    /// <summary>
    /// �ÓI�ȃX�e�[�W���b�V���̐���
    /// </summary>
    /// <returns>true : ����, false : ������</returns>
    bool CreateStaticStageMesh(void);

public:

    /// <summary>
    /// �X�e�[�W�̓ǂݍ���
    /// </summary>
    /// <param name="path">�X�e�[�W�f�[�^�t�@�C���p�X</param>
    /// <returns>true : ����, false : �G���[</returns>
    bool Load(const std::string& path);

    /// <summary>
    /// ������
    /// </summary>
    void Initialize(void);

    /// <summary>
    /// �X�V
    /// </summary>
    void Update(float delta);

    /// <summary>
    /// �`��
    /// </summary>
    void Render(void);

    /// <summary>
    /// ���
    /// </summary>
    void Release(void);

    /// <summary>
    /// �ÓI�ȃX�e�[�W���b�V���𐶐��������̃t���O�擾
    /// </summary>
    /// <returns>�ÓI�ȃX�e�[�W���b�V���𐶐��������̃t���O</returns>
    bool IsCreateStaticStageMesh(void) const;

    /// <summary>
    /// �ÓI�ȃX�e�[�W���b�V���̎擾
    /// </summary>
    /// <returns>�������Ă��Ȃ��ꍇ nullptr ���Ԃ�</returns>
    MeshPtr GetStaticStageMesh(void);

    /// <summary>
    /// �G�̏o���ʒu�z��̎擾
    /// </summary>
    /// <returns>�G�̏o���ʒu�z��</returns>
    EnemySpawnArray& GetEnemySpawnArray(void);

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    GimmickArray& GetGimmickArray(void);
};

