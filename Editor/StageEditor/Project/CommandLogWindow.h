#pragma once
#include "Singleton.h"
#include <vector>
#include <string>

/// <summary>
/// �R�}���h���O�E�B���h�E
/// </summary>
class CommandLogWindow : public Singleton<CommandLogWindow> {
private:

	std::vector<std::string> _logs;

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

	/// <summary>
	/// ���O�̒ǉ�
	/// </summary>
	/// <param name="log">���O</param>
	void AddLog(const std::string& log);
};

