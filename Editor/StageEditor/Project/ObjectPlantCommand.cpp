#include "ObjectPlantCommand.h"
#include "ObjectWindow.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="target">対象</param>
ObjectPlantCommand::ObjectPlantCommand(ObjectData* target) {
    _object = *target;
}

/// <summary>
/// 登録
/// </summary>
void ObjectPlantCommand::Register(void) {
}

/// <summary>
/// 実行
/// </summary>
void ObjectPlantCommand::Exec(void) {
    ObjectWindow::GetInstance().Add(_object);
}

/// <summary>
/// 元に戻す
/// </summary>
void ObjectPlantCommand::Undo(void) {
    ObjectWindow::GetInstance().Remove(_object);
}

/// <summary>
/// コマンド名の取得
/// </summary>
/// <returns>コマンド名</returns>
const std::string ObjectPlantCommand::GetName(void) const {
    return "ObjectPlantCommand";
}
