#pragma once
#include <memory>
#include <string>

/// <summary>
/// コマンドインターフェース
/// </summary>
class ICommand : public std::enable_shared_from_this<ICommand> {
public:
	/// <summary>
	/// 登録
	/// </summary>
	virtual void Register(void) = 0;

	/// <summary>
	/// 実行
	/// </summary>
	virtual void Exec(void) = 0;

	/// <summary>
	/// 元に戻す
	/// </summary>
	virtual void Undo(void) = 0;

	/// <summary>
	/// コマンド名の取得
	/// </summary>
	/// <returns>コマンド名</returns>
	virtual const std::string GetName(void) const = 0;
};

//! コマンドポインタ
using ICommandPtr = std::shared_ptr<ICommand>;