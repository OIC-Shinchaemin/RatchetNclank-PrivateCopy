#include "ObjectRemoveCommand.h"
#include "ObjectWindow.h"

/// <summary>
/// コンストラクタ
/// </summary>
ObjectRemoveCommand::ObjectRemoveCommand(void) {
    ObjectData* select_data = ObjectWindow::GetInstance().GetSelectObjectData();
    _data         = *select_data;
    _insert_point = ObjectWindow::GetInstance().GetSelectNo();
}

/// <summary>
/// 登録
/// </summary>
void ObjectRemoveCommand::Register(void) {
}

/// <summary>
/// 実行
/// </summary>
void ObjectRemoveCommand::Exec(void) {
    ObjectWindow::GetInstance().Remove(_data);
}

/// <summary>
/// 元に戻す
/// </summary>
void ObjectRemoveCommand::Undo(void) {
    ObjectList::iterator it = ObjectWindow::GetInstance().GetObjectList().begin();
    ObjectWindow::GetInstance().GetObjectList().insert(it + _insert_point, _data);
}

/// <summary>
/// コマンド名の取得
/// </summary>
/// <returns>コマンド名</returns>
const std::string ObjectRemoveCommand::GetName(void) const {
    return "ObjectRemoveCommand";
}
