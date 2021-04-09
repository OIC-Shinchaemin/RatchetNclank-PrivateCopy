#include "CommandManager.h"
#include "CommandLogWindow.h"

/// <summary>
/// �R�}���h�z��̃T�C�Y����
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
/// �R���X�g���N�^
/// </summary>
CommandManager::CommandManager(void)
	: _exec_stack()
	, _redo_stack() {
	// �ő匏����o�^
	_exec_stack.reserve(command_count);
	_redo_stack.reserve(command_count);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CommandManager::~CommandManager(void) {
}

/// <summary>
/// ��蒼��
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
/// ���ɖ߂�
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
/// �R�}���h�̓o�^
/// </summary>
/// <param name="cmd">�o�^����R�}���h</param>
void CommandManager::Register(const ICommandPtr& cmd) {
	cmd->Exec();
	_exec_stack.push_back(cmd);
	_redo_stack.clear();
	SizeControll();
	CommandLogWindow::GetInstance().AddLog("exec:" + cmd->GetName());
}

/// <summary>
/// ���Z�b�g
/// </summary>
void CommandManager::Reset(void) {
	_exec_stack.clear();
	_redo_stack.clear();
	CommandLogWindow::GetInstance().AddLog("clear");
}

/// <summary>
/// �R�}���h�̎擾
/// </summary>
/// <returns>�z��</returns>
const std::vector<ICommandPtr>& CommandManager::GetExecArray(void) const {
	return _exec_stack;
}
const std::vector<ICommandPtr>& CommandManager::GetRedoArray(void) const {
	return _redo_stack;
}
