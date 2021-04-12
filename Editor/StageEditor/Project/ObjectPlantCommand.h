#pragma once
#include "Command.h"
#include "Define.h"

/// <summary>
/// オブジェクト設置コマンド
/// </summary>
class ObjectPlantCommand : public ICommand {
private:

    //! 設置するオブジェクト
	ObjectData _object;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="target">対象</param>
	ObjectPlantCommand(ObjectData* target);

	/// <summary>
	/// 登録
	/// </summary>
	virtual void Register(void) override;

	/// <summary>
	/// 実行
	/// </summary>
	virtual void Exec(void) override;

	/// <summary>
	/// 元に戻す
	/// </summary>
	virtual void Undo(void) override;

	/// <summary>
	/// コマンド名の取得
	/// </summary>
	/// <returns>コマンド名</returns>
	virtual const std::string GetName(void) const override;
};

