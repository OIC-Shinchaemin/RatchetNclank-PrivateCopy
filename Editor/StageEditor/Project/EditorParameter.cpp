#include "EditorParameter.h"
#include "ParameterMap.h"
#include "WindowKeyName.h"

//! 各ゲッター
bool EditorParameter::IsShowMouseInfo(void) const {
    return _show_mouseinfo;
}

bool EditorParameter::IsShowIsItemInfo(void) const {
    return _show_isiteminfo;
}

bool EditorParameter::IsShowRectInfo(void) const {
    return _show_rectinfo;
}

bool EditorParameter::IsShowDemoWindow(void) const {
    return _show_demo_window;
}

bool EditorParameter::IsShowMeshWindow(void) const {
    return _show_mesh_window;
}

bool EditorParameter::IsShowObjectWindow(void) const {
    return _show_object_window;
}

bool EditorParameter::IsShowToolMenu(void) const {
    return _show_tool_menu;
}

bool EditorParameter::IsShowMainMenu(void) const {
    return _show_main_menu;
}

bool EditorParameter::IsShowGrid(void) const {
    return _show_grid;
}

bool EditorParameter::IsShowCommandLogWindow(void) const {
    return _show_commandlog_window;
}

int EditorParameter::GetEditMode(void) const {
    return _edit_mode;
}

std::string EditorParameter::GetResourcePath(void) const {
    return _resource_path;
}

//! 各セッター
void EditorParameter::SetResourcePath(const std::string& path) {
    _resource_path = path;
    ParameterMap<std::string>::GetInstance().Set("resource_path", &_resource_path);
}

// ********************************************************************************
/// <summary>
/// コンストラクタ
/// </summary>
/// <created>いのうえ,2021/03/17</created>
/// <changed>いのうえ,2021/03/17</changed>
// ********************************************************************************
EditorParameter::EditorParameter(void) {
    ParameterMap<bool>::GetInstance().Set(WindowKeyName::DebugMouseInfo     , &_show_mouseinfo);
    ParameterMap<bool>::GetInstance().Set(WindowKeyName::DebugIsItemInfo    , &_show_isiteminfo);
    ParameterMap<bool>::GetInstance().Set(WindowKeyName::DebugWindowRectInfo, &_show_rectinfo);
    ParameterMap<bool>::GetInstance().Set(WindowKeyName::DebugDemoWindow    , &_show_demo_window);
    ParameterMap<bool>::GetInstance().Set(WindowKeyName::MeshWindow         , &_show_object_window);
    ParameterMap<bool>::GetInstance().Set(WindowKeyName::ObjectWindow       , &_show_mesh_window);
    ParameterMap<bool>::GetInstance().Set(WindowKeyName::ToolMenu           , &_show_tool_menu);
    ParameterMap<bool>::GetInstance().Set(WindowKeyName::MainMenu           , &_show_main_menu);
    ParameterMap<bool>::GetInstance().Set(WindowKeyName::CommandLogWindow   , &_show_commandlog_window);
    ParameterMap<bool>::GetInstance().Set("show_grid"                       , &_show_grid);

	ParameterMap<float>::GetInstance().Set("mesh_view_zoom", &_mesh_view_zoom);

	ParameterMap<int>::GetInstance().Set("edit_mode"   , &_edit_mode);
	ParameterMap<int>::GetInstance().Set("grid_between", &_grid_between);
	ParameterMap<int>::GetInstance().Set("grid_size"   , &_grid_size);

	ParameterMap<Vector4>::GetInstance().Set("background_color", &_background_color);

	ParameterMap<std::string>::GetInstance().Set("open_file_name", &_open_file_name);
}

// ********************************************************************************
/// <summary>
/// デストラクタ
/// </summary>
/// <created>いのうえ,2021/03/17</created>
/// <changed>いのうえ,2021/03/17</changed>
// ********************************************************************************
EditorParameter::~EditorParameter(void) {
}
