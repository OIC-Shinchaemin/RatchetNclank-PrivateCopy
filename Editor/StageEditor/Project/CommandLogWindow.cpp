#include "CommandLogWindow.h"
#include "CommandManager.h"
#include "GuiWindowRect.h"
#include "WindowKeyName.h"
#include <MofImGui/MofImGui.h>
#include "ParameterMap.h"

CommandLogWindow::CommandLogWindow(void) {
}

CommandLogWindow::~CommandLogWindow(void) {
}

void CommandLogWindow::Show(void) {
	ImGui::Begin("command log window", ParameterMap<bool>::GetInstance().Get(WindowKeyName::CommandLogWindow)); {
	    GuiWindowRect::GetInstance().Add(WindowKeyName::CommandLogWindow);
	    for (const auto& it : _logs) {
			ImGui::Text(it.c_str());
		}
	}
	ImGui::End();
}

void CommandLogWindow::AddLog(const std::string& log) {
	_logs.push_back(log);
	if (_logs.size() >= 100) {
		_logs.erase(_logs.begin());
	}
}
