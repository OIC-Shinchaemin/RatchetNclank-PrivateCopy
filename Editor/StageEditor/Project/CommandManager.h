#pragma once
#include "Singleton.h"
#include "Command.h"
#include <vector>

constexpr unsigned int command_count = 50;

/// <summary>
/// コマンド管理クラス
/// </summary>
class CommandManager : public Singleton<CommandManager> {
private:

	//! 実行スタック
	std::vector<ICommandPtr> _exec_stack;

	//! やり直しスタック
	std::vector<ICommandPtr> _redo_stack;

	/// <summary>
	/// コマンド配列のサイズ制御
	/// </summary>
	void SizeControll(void);

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	CommandManager(void);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~CommandManager(void);

	/// <summary>
	/// やり直し
	/// </summary>
	void Redo(void);

	/// <summary>
	/// 元に戻す
	/// </summary>
	void Undo(void);

	/// <summary>
	/// コマンドの登録
	/// </summary>
	/// <param name="cmd">登録するコマンド</param>
	void Register(const ICommandPtr& cmd);

    /// <summary>
    /// コマンドの取得
    /// </summary>
    /// <returns>配列</returns>
    const std::vector<ICommandPtr>& GetExecArray(void) const;
    const std::vector<ICommandPtr>& GetRedoArray(void) const;
};

