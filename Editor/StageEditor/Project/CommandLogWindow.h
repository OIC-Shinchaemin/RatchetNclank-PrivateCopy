#pragma once
#include "Singleton.h"

/// <summary>
/// �R�}���h���O�E�B���h�E
/// </summary>
class CommandLogWindow : public Singleton<CommandLogWindow> {
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CommandLogWindow(void);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CommandLogWindow(void);

	/// <summary>
	/// �\��
	/// </summary>
	void Show(void);
};

