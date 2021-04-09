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
	    GuiWindowRect::GetInstance().Add(WindowKeyName::MeshWindow);

	    ImGui::BeginChild("command exec");
		for (const auto& it : CommandManager::GetInstance().GetExecArray()) {
			ImGui::Text(it->GetName().c_str());
		}
	    ImGui::EndChild();
		ImGui::SameLine();
		ImGui::BeginChild("command redo");
		for (const auto& it : CommandManager::GetInstance().GetRedoArray()) {
			ImGui::Text(it->GetName().c_str());
		}
		ImGui::EndChild();
	}
	ImGui::End();
}
