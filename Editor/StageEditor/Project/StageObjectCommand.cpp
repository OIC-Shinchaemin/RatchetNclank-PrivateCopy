#include "StageObjectCommand.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="target">�Ώ�</param>
StageObjectCommand::StageObjectCommand(ObjectData* target)
    : _target_pointer(target)
    , _prev(*target)
    , _next() {
}

/// <summary>
/// �o�^
/// </summary>
void StageObjectCommand::Register(void) {
    _next = *_target_pointer;
}

/// <summary>
/// ���s
/// </summary>
void StageObjectCommand::Exec(void) {
    (*_target_pointer) = _next;
}

/// <summary>
/// ���ɖ߂�
/// </summary>
void StageObjectCommand::Undo(void) {
    (*_target_pointer) = _prev;
}

/// <summary>
/// �R�}���h���̎擾
/// </summary>
/// <returns>�R�}���h��</returns>
const std::string StageObjectCommand::GetName(void) const {
    return "StageObjectCommand";
}
