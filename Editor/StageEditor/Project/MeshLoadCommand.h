#pragma once
#include "Command.h"
#include "Define.h"

/// <summary>
/// ���b�V���ǂݍ��݃R�}���h
/// </summary>
class MeshLoadCommand : public ICommand {
private:

	//! �Ǘ��Ώ�
	std::string _file_name;
	std::string _key_name;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="key">�L�[��</param>
	/// <param name="file">�t�@�C���p�X</param>
	MeshLoadCommand(const std::string& key, const std::string& file);

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

