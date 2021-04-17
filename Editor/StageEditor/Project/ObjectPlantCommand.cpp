#include "ObjectPlantCommand.h"
#include "ObjectWindow.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="target">�Ώ�</param>
ObjectPlantCommand::ObjectPlantCommand(ObjectData* target) {
    _object = *target;
}

/// <summary>
/// �o�^
/// </summary>
void ObjectPlantCommand::Register(void) {
}

/// <summary>
/// ���s
/// </summary>
void ObjectPlantCommand::Exec(void) {
    ObjectWindow::GetInstance().Add(_object);
}

/// <summary>
/// ���ɖ߂�
/// </summary>
void ObjectPlantCommand::Undo(void) {
    ObjectWindow::GetInstance().Remove(_object);
}

/// <summary>
/// �R�}���h���̎擾
/// </summary>
/// <returns>�R�}���h��</returns>
const std::string ObjectPlantCommand::GetName(void) const {
    return "ObjectPlantCommand";
}
