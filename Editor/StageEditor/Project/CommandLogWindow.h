#pragma once
#include "Singleton.h"
#include <vector>
#include <string>

/// <summary>
/// コマンドログウィンドウ
/// </summary>
class CommandLogWindow : public Singleton<CommandLogWindow> {
private:

	std::vector<std::string> _logs;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	CommandLogWindow(void);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~CommandLogWindow(void);

	/// <summary>
	/// 表示
	/// </summary>
	void Show(void);

	/// <summary>
	/// ログの追加
	/// </summary>
	/// <param name="log">ログ</param>
	void AddLog(const std::string& log);
};

