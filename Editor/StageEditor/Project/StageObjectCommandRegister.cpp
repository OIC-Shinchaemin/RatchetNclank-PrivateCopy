#include "StageObjectCommandRegister.h"
#include "CommandManager.h"
#include "StageObjectCommand.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="target">対象</param>
StageObjectCommandRegister::StageObjectCommandRegister(bool* target, ObjectData* data)
    : _exec_flag(target)
    , _run_flag(false)
    , _data(data) {
}

/// <summary>
/// 更新
/// </summary>
void StageObjectCommandRegister::Update(void) {
    // 実行開始
    if (*_exec_flag && !_run_flag) {
        _run_flag = true;
        _command  = std::make_shared<StageObjectCommand>(_data);
    }
    // 実行されていない場合は更新しない
    if (!_run_flag) {
        return;
    }
    // 実行終了
    if (!(*_exec_flag)) {
        _run_flag = false;
        _command->Register();
        CommandManager::GetInstance().Register(_command);
        _command  = nullptr;
    }
}

/// <summary>
/// データの登録
/// </summary>
/// <param name="data">データ</param>
void StageObjectCommandRegister::SetObjectData(ObjectData* data) {
    _data = data;
}
