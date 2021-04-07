#pragma once

/// <summary>
/// 
/// </summary>
class ICommand {
private:

public:
	virtual void Push() = 0;
	virtual void Exec() = 0;
	virtual void Undo() = 0;
};

#include	<Mof.h>
class MoveCommand : public ICommand
{
private:
	Vector3 move_;
	CSphere* pTarget;
public:
	MoveCommand(Vector3 move, CSphere* target)
		: move_(move) , pTarget(target){}

	void Push() override {
	}
	void Exec() override {
		pTarget->Translation(move_);
	}

	void Undo() override {
		pTarget->Translation(-move_);
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
		, pTarget(target) {}

	void Push() override {
		next_ = pTarget->Position;
	}
	void Exec() override {
		pTarget->Position = next_;
	}

	void Undo() override {
		pTarget->Position = prev_;
	}
};