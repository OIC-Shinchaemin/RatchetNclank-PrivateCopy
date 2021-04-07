#pragma once
#include "Command.h"
#include <vector>

constexpr unsigned int command_count = 50;

/// <summary>
/// �R�}���h�Ǘ��N���X
/// </summary>
class CommandManager {
private:

	//! ���s�X�^�b�N
	std::vector<ICommandPtr> _exec_stack;

	//! ��蒼���X�^�b�N
	std::vector<ICommandPtr> _redo_stack;

	/// <summary>
	/// �R�}���h�z��̃T�C�Y����
	/// </summary>
	void SizeControll(void);

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CommandManager(void);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CommandManager(void);

	/// <summary>
	/// ��蒼��
	/// </summary>
	void Redo(void);

	/// <summary>
	/// ���ɖ߂�
	/// </summary>
	void Undo(void);

	/// <summary>
	/// �R�}���h�̓o�^
	/// </summary>
	/// <param name="cmd">�o�^����R�}���h</param>
	void Register(const ICommandPtr& cmd);
};

