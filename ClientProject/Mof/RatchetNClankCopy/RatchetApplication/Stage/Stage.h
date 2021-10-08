#pragma once
#include "StageObject.h"
#include "Gimmick/GimmickBase.h"
#include "Gimmick/WoodBox.h"
#include "Base/Core/Timer.h"


// pair<builder_path, pos_data>
using EnemySpawnData  = std::pair<std::string, StageObjectPtr>;
using EnemySpawnArray = std::vector<EnemySpawnData>;

/// <summary>
/// �X�e�[�W�N���X
/// </summary>
class Stage {
private:

    //! �X�e�[�W�Ŏg�p���郁�b�V���̔z��
    MeshArray           _mesh_array;

    //! �ÓI�ȃI�u�W�F�N�g�̔z��
    StageObjectArray    _static_object_array;

    //! �G�̏o���ʒu�z��
    EnemySpawnArray     _ENEMY_spawn_array;

    //! �M�~�b�N�̔z��
    GimmickArray        _gimmick_array;

    //! ���n�I�u�W�F�N�g�̔z��
    WoodBoxArray        _woodbox_array;

    std::vector<bool>   _box_enable_array_prev;

    bool                _init_flag;

    //! 
    base::core::Timer _cursor_active_timer;
    //! 
    base::core::Timer _cursor_blinking_timer;
    //! �J�[�\���e�N�X�`��
    Mof::CTexture _cursor_texture;

    void RenderObject(const StageObjectPtr& obj);

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

    MeshArray& GetMeshArray(void);

    StageObjectArray& GetStaticObjectArray(void);

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

    WoodBoxArray& GetWoodBoxArray(void);
};

