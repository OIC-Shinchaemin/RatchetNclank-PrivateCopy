#pragma once
#include "Command.h"
#include "Define.h"

/// <summary>
/// メッシュ読み込みコマンド
/// </summary>
class MeshLoadCommand : public ICommand {
private:

	//! 管理対象
	std::string _file_name;
	std::string _key_name;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="key">キー名</param>
	/// <param name="file">ファイルパス</param>
	MeshLoadCommand(const std::string& key, const std::string& file);

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

