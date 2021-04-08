#pragma once
#include "Singleton.h"
#include "Command.h"
#include <vector>

constexpr unsigned int command_count = 50;

/// <summary>
/// �R�}���h�Ǘ��N���X
/// </summary>
class CommandManager : public Singleton<CommandManager> {
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

    /// <summary>
    /// �R�}���h�̎擾
    /// </summary>
    /// <returns>�z��</returns>
    const std::vector<ICommandPtr>& GetExecArray(void) const;
    const std::vector<ICommandPtr>& GetRedoArray(void) const;
};

