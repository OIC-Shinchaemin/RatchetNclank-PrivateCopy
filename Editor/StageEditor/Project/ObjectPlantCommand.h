#pragma once
#include "Command.h"
#include "Define.h"

/// <summary>
/// �I�u�W�F�N�g�ݒu�R�}���h
/// </summary>
class ObjectPlantCommand : public ICommand {
private:

    //! �ݒu����I�u�W�F�N�g
	ObjectData _object;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="target">�Ώ�</param>
	ObjectPlantCommand(ObjectData* target);

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

