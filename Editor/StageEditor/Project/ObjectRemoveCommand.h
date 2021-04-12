#pragma once
#include "Command.h"
#include "Define.h"

/// <summary>
/// 削除コマンド
/// </summary>
class ObjectRemoveCommand : public ICommand {
private:

	//! 対象データ
	ObjectData _data;
	//! 消すデータのUndo用挿入位置
	int        _insert_point;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ObjectRemoveCommand(void);

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

