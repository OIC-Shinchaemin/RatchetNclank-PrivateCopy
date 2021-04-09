#pragma once
#include "Command.h"
#include "Define.h"

/// <summary>
/// 
/// </summary>
class MeshRemoveCommand : public ICommand {
private:

	//! �Ώۃf�[�^
	std::string _key;
	std::string _file_name;
	
	//! �����f�[�^��Undo�p�}���ʒu
	int         _insert_point;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	MeshRemoveCommand(void);

	/// <summary>
	/// �o�^
	/// </summary>
	virtual void Register(void) override;

	/// <summary>
	/// ���s
	/// </summary>
	virtual void Exec(void) override;

	/// <summary>
	/// ���ɖ߂�
	/// </summary>
	virtual void Undo(void) override;

	/// <summary>
	/// �R�}���h���̎擾
	/// </summary>
	/// <returns>�R�}���h��</returns>
	virtual const std::string GetName(void) const override;
};

