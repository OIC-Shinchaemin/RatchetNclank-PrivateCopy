#include "StageObjectCommand.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="target">対象</param>
StageObjectCommand::StageObjectCommand(ObjectData* target)
    : _target_pointer(target)
    , _prev(*target)
    , _next() {
}

/// <summary>
/// 登録
/// </summary>
void StageObjectCommand::Register(void) {
    _next = *_target_pointer;
}

/// <summary>
/// 実行
/// </summary>
void StageObjectCommand::Exec(void) {
    (*_target_pointer) = _next;
}

/// <summary>
/// 元に戻す
/// </summary>
void StageObjectCommand::Undo(void) {
    (*_target_pointer) = _prev;
}

/// <summary>
/// コマンド名の取得
/// </summary>
/// <returns>コマンド名</returns>
const std::string StageObjectCommand::GetName(void) const {
    return "StageObjectCommand";
}
