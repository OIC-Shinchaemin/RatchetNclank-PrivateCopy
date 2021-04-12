#include "ObjectRemoveCommand.h"
#include "ObjectWindow.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ObjectRemoveCommand::ObjectRemoveCommand(void) {
    ObjectData* select_data = ObjectWindow::GetInstance().GetSelectObjectData();
    _data         = *select_data;
    _insert_point = ObjectWindow::GetInstance().GetSelectNo();
}

/// <summary>
/// �o�^
/// </summary>
void ObjectRemoveCommand::Register(void) {
}

/// <summary>
/// ���s
/// </summary>
void ObjectRemoveCommand::Exec(void) {
    ObjectWindow::GetInstance().Remove(_data);
}

/// <summary>
/// ���ɖ߂�
/// </summary>
void ObjectRemoveCommand::Undo(void) {
    ObjectList::iterator it = ObjectWindow::GetInstance().GetObjectList().begin();
    ObjectWindow::GetInstance().GetObjectList().insert(it + _insert_point, _data);
}

/// <summary>
/// �R�}���h���̎擾
/// </summary>
/// <returns>�R�}���h��</returns>
const std::string ObjectRemoveCommand::GetName(void) const {
    return "ObjectRemoveCommand";
}
