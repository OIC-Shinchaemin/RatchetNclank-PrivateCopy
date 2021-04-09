#pragma once
#include "Singleton.h"

/// <summary>
/// コマンドログウィンドウ
/// </summary>
class CommandLogWindow : public Singleton<CommandLogWindow> {
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
};

