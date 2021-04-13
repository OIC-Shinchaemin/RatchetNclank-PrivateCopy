#include "CommandManager.h"
#include "CommandLogWindow.h"

/// <summary>
/// コマンド配列のサイズ制御
/// </summary>
void CommandManager::SizeControll(void) {
	if (_redo_stack.size() > command_count) {
		_redo_stack.erase(_redo_stack.begin());
	}
	if (_exec_stack.size() > command_count) {
		_exec_stack.erase(_exec_stack.begin());
	}
}

/// <summary>
/// コンストラクタ
/// </summary>
CommandManager::CommandManager(void)
	: _exec_stack()
	, _redo_stack() {
	// 最大件数を登録
	_exec_stack.reserve(command_count);
	_redo_stack.reserve(command_count);
}

/// <summary>
/// デストラクタ
/// </summary>
CommandManager::~CommandManager(void) {
}

/// <summary>
/// やり直し
/// </summary>
void CommandManager::Redo(void) {
	if (_redo_stack.size() <= 0) {
		return;
	}
	ICommandPtr cmd = _redo_stack.back();
	cmd->Exec();
	_redo_stack.pop_back();
	_exec_stack.push_back(cmd);
	SizeControll();
	CommandLogWindow::GetInstance().AddLog("redo:" + cmd->GetName());
}

/// <summary>
/// 元に戻す
/// </summary>
void CommandManager::Undo(void) {
	if (_exec_stack.size() <= 0) {
		return;
	}
	ICommandPtr cmd = _exec_stack.back();
	cmd->Undo();
	_exec_stack.pop_back();
	_redo_stack.push_back(cmd);
	SizeControll();
	CommandLogWindow::GetInstance().AddLog("undo:" + cmd->GetName());
}

/// <summary>
/// コマンドの登録
/// </summary>
/// <param name="cmd">登録するコマンド</param>
void CommandManager::Register(const ICommandPtr& cmd) {
	cmd->Exec();
	_exec_stack.push_back(cmd);
	_redo_stack.clear();
	SizeControll();
	CommandLogWindow::GetInstance().AddLog("exec:" + cmd->GetName());
}

/// <summary>
/// リセット
/// </summary>
void CommandManager::Reset(void) {
	_exec_stack.clear();
	_redo_stack.clear();
	CommandLogWindow::GetInstance().AddLog("clear");
}

/// <summary>
/// コマンドの取得
/// </summary>
/// <returns>配列</returns>
const std::vector<ICommandPtr>& CommandManager::GetExecArray(void) const {
	return _exec_stack;
}
const std::vector<ICommandPtr>& CommandManager::GetRedoArray(void) const {
	return _redo_stack;
}
