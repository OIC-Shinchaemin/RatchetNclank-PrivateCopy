#include "StageObjectCommandRegister.h"
#include "CommandManager.h"
#include "StageObjectCommand.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="target">�Ώ�</param>
StageObjectCommandRegister::StageObjectCommandRegister(bool* target, ObjectData* data)
    : _exec_flag(target)
    , _run_flag(false)
    , _data(data) {
}

/// <summary>
/// �X�V
/// </summary>
void StageObjectCommandRegister::Update(void) {
    // ���s�J�n
    if (*_exec_flag && !_run_flag) {
        _run_flag = true;
        _command  = std::make_shared<StageObjectCommand>(_data);
    }
    // ���s����Ă��Ȃ��ꍇ�͍X�V���Ȃ�
    if (!_run_flag) {
        return;
    }
    // ���s�I��
    if (!(*_exec_flag)) {
        _run_flag = false;
        _command->Register();
        CommandManager::GetInstance().Register(_command);
        _command  = nullptr;
    }
}

/// <summary>
/// �f�[�^�̓o�^
/// </summary>
/// <param name="data">�f�[�^</param>
void StageObjectCommandRegister::SetObjectData(ObjectData* data) {
    _data = data;
}
