#pragma once
#include "Command.h"
#include "Define.h"

/// <summary>
/// ステージオブジェクトコマンドクラス
/// </summary>
class StageObjectCommand : public ICommand {
private:

	//! 変更前
	ObjectData  _prev;
	//! 変更後
	ObjectData  _next;
	//! 対象
	ObjectData* _target_pointer;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="target">対象</param>
	StageObjectCommand(ObjectData* target);

	/// <summary>
	/// 登録
	/// </summary>
	virtual void Register(void) override;

	/// <summary>
	/// 実行
	/// </summary>
	virtual void Exec(void) override;

	/// <summary>
	/// 元に戻す
	/// </summary>
	virtual void Undo(void) override;

	/// <summary>
	/// コマンド名の取得
	/// </summary>
	/// <returns>コマンド名</returns>
	virtual const std::string GetName(void) const override;
};

