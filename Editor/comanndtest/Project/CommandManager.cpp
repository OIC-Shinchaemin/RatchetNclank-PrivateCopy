#include "CommandManager.h"

CommandManager::CommandManager(void)
: _execstack()
, _redostack(){
}

CommandManager::~CommandManager(void)
{
}

void CommandManager::Redo(void)
{
	ICommand* cmd = _redostack.back();
	cmd->Exec();
	_redostack.pop_back();
	_execstack.push_back(cmd);
}

void CommandManager::Undo(void)
{
	ICommand* cmd = _execstack.back();
	cmd->Undo();
	_execstack.pop_back();
	_redostack.push_back(cmd);
}

void CommandManager::PushCommand(ICommand* cmd) {
	cmd->Exec();
	_execstack.push_back(cmd);
	_redostack.clear();
}