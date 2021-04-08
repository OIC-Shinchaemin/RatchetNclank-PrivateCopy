#pragma once
#include <memory>
#include <string>

/// <summary>
/// コマンドインターフェース
/// </summary>
class ICommand : public std::enable_shared_from_this<ICommand> {
public:
	/// <summary>
	/// 登録
	/// </summary>
	virtual void Register(void) = 0;

	/// <summary>
	/// 実行
	/// </summary>
	virtual void Exec(void) = 0;

	/// <summary>
	/// 元に戻す
	/// </summary>
	virtual void Undo(void) = 0;

	/// <summary>
	/// コマンド名の取得
	/// </summary>
	/// <returns>コマンド名</returns>
	virtual const std::string GetName(void) const = 0;
};

//! コマンドポインタ
using ICommandPtr = std::shared_ptr<ICommand>;

// 以下TEST

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