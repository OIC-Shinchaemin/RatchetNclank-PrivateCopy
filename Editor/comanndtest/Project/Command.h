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

// �ȉ�TEST

#include <Mof.h>
class MoveCommand : public ICommand
{
private:
	Vector3 move_;
	CSphere* pTarget;
public:
	MoveCommand(Vector3 move, CSphere* target)
		: move_(move) 
		, pTarget(target) {
	}

	void Register(void) override {
	}

	void Exec(void) override {
		pTarget->Translation(move_);
	}

	void Undo(void) override {
		pTarget->Translation(-move_);
	}

	const std::string GetName(void) const override {
		return "MoveCommand";
	}
};

class PositionCommand : public ICommand
{
private:
	Vector3 prev_;
	Vector3 next_;
	CSphere* pTarget;
public:
	PositionCommand(CSphere* target)
		: prev_(target->Position.x, target->Position.y, target->Position.z)
		, next_(0,0,0)
		, pTarget(target) {
	}

	void Register(void) override {
		next_ = pTarget->Position;
	}

	void Exec(void) override {
		pTarget->Position = next_;
	}

	void Undo(void) override {
		pTarget->Position = prev_;
	}

	const std::string GetName(void) const override {
		return "PositionCommand";
	}
};