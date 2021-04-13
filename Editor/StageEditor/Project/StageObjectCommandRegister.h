#pragma once
#include "Command.h"
#include "Define.h"

/// <summary>
/// コマンド登録クラス
/// </summary>
class StageObjectCommandRegister {
private:

    //! 実行フラグ
    bool*       _exec_flag;

    //! 実行中フラグ
    bool        _run_flag;

    //! コマンド
    ICommandPtr _command;

    //! 対象データ
    ObjectData* _data;

public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="target">対象</param>
    StageObjectCommandRegister(bool* target, ObjectData* data);

    /// <summary>
    /// 更新
    /// </summary>
    void Update(void);

    /// <summary>
    /// データの登録
    /// </summary>
    /// <param name="data">データ</param>
    void SetObjectData(ObjectData* data);
};

