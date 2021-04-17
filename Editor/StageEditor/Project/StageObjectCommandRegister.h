#pragma once
#include "Command.h"
#include "Define.h"

/// <summary>
/// �R�}���h�o�^�N���X
/// </summary>
class StageObjectCommandRegister {
private:

    //! ���s�t���O
    bool*       _exec_flag;

    //! ���s���t���O
    bool        _run_flag;

    //! �R�}���h
    ICommandPtr _command;

    //! �Ώۃf�[�^
    ObjectData* _data;

public:

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="target">�Ώ�</param>
    StageObjectCommandRegister(bool* target, ObjectData* data);

    /// <summary>
    /// �X�V
    /// </summary>
    void Update(void);

    /// <summary>
    /// �f�[�^�̓o�^
    /// </summary>
    /// <param name="data">�f�[�^</param>
    void SetObjectData(ObjectData* data);
};

