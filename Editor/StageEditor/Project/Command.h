#pragma once
#include <memory>
#include <string>

/// <summary>
/// �R�}���h�C���^�[�t�F�[�X
/// </summary>
class ICommand : public std::enable_shared_from_this<ICommand> {
public:
	/// <summary>
	/// �o�^
	/// </summary>
	virtual void Register(void) = 0;

	/// <summary>
	/// ���s
	/// </summary>
	virtual void Exec(void) = 0;

	/// <summary>
	/// ���ɖ߂�
	/// </summary>
	virtual void Undo(void) = 0;

	/// <summary>
	/// �R�}���h���̎擾
	/// </summary>
	/// <returns>�R�}���h��</returns>
	virtual const std::string GetName(void) const = 0;
};

//! �R�}���h�|�C���^
using ICommandPtr = std::shared_ptr<ICommand>;