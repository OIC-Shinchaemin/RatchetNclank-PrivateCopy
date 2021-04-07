#pragma once
#include "Command.h"
#include <vector>

constexpr unsigned int command_count = 16;

/// <summary>
/// 
/// </summary>
class CommandManager {
private:

	std::vector<ICommand*> _execstack;
	std::vector<ICommand*> _redostack;

public:

	CommandManager(void);
	~CommandManager(void);

	void Redo(void);
	void Undo(void);

	void PushCommand(ICommand* cmd);
};

