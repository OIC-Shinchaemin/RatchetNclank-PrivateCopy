#include "MainMenu.h"
#include "Define.h"
#include "ParameterMap.h"
#include "WindowKeyName.h"
#include "GuiWindowRect.h"
#include "ActionManager.h"
#include "ActionKeyName.h"

void MainMenu::File(void) {
    if (ImGui::MenuItem("new", "Ctrl + N")) {};
    if (ImGui::MenuItem("open", "Ctrl + O")) {
        LoadData data;
        std::string* file_name = ParameterMap<std::string>::GetInstance().Get("open_file_name");
        rapidjson::Document project_data;
        *file_name = "test.json";
        data.first  = *file_name;
        data.second = &project_data;
        if (ActionManager::GetInstance().Action(ActionKeyName::LoadProject, &data)) {
            ParseData save_data;
            std::get<0>(save_data) = &project_data;
            std::get<1>(save_data) = ParameterMap<MeshList>::GetInstance().Get("mesh_list");
            std::get<2>(save_data) = ParameterMap<ObjectList>::GetInstance().Get("object_list");
            if (ActionManager::GetInstance().Action(ActionKeyName::ProjectDataParse, &save_data)) {
                
            }
        }
    };
    if (ImGui::MenuItem("close", "Ctrl + Alt + C")) {};
    ImGui::Separator();
    if (ImGui::MenuItem("save", "Ctrl + S")) {
        SaveData data;
        std::string* file_name = ParameterMap<std::string>::GetInstance().Get("open_file_name");
        *file_name = "test.json";
        std::get<0>(data) = *file_name;
        std::get<1>(data) = ParameterMap<MeshList>::GetInstance().Get("mesh_list");
        std::get<2>(data) = ParameterMap<ObjectList>::GetInstance().Get("object_list");
        if (ActionManager::GetInstance().Action(ActionKeyName::SaveProject, &data)) {

        }
    };
    if (ImGui::MenuItem("save as...", "Ctrl + Shift + S")) {};
    ImGui::Separator();
    if (ImGui::MenuItem("quit", "Alt + F4")) { PostQuitMessage(0); };
}

void MainMenu::Edit(void) {
    if (ImGui::BeginMenu("background color...")) {
        Vector4* back_color_pointer = ParameterMap<Vector4>::GetInstance().Get("background_color");
        ImGui::ColorEdit4("background color", *back_color_pointer);
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("grid...")) {
        ImGui::DragInt("between", ParameterMap<int>::GetInstance().Get("grid_between"), 1, 1, MOF_S32_MAX);
        ImGui::DragInt("size"   , ParameterMap<int>::GetInstance().Get("grid_size")   , 1, 1, MOF_S32_MAX);
        ImGui::EndMenu();
    }
}

void MainMenu::View(void) {
    bool* show_mouseinfo_pointer    = ParameterMap<bool>::GetInstance().Get(WindowKeyName::DebugMouseInfo);
    bool* show_isiteminfo_pointer   = ParameterMap<bool>::GetInstance().Get(WindowKeyName::DebugIsItemInfo);
    bool* show_rectinfo_pointer     = ParameterMap<bool>::GetInstance().Get(WindowKeyName::DebugWindowRectInfo);
    bool* show_demowindow_pointer   = ParameterMap<bool>::GetInstance().Get(WindowKeyName::DebugDemoWindow);
    bool* show_meshwindow_pointer   = ParameterMap<bool>::GetInstance().Get(WindowKeyName::MeshWindow);
    bool* show_objectwindow_pointer = ParameterMap<bool>::GetInstance().Get(WindowKeyName::ObjectWindow);
    bool* show_toolmenu_pointer     = ParameterMap<bool>::GetInstance().Get(WindowKeyName::ToolMenu);
    bool* show_grid_pointer         = ParameterMap<bool>::GetInstance().Get("show_grid");
    std::function<void(std::string, bool*)> toggle_bool_item = [](std::string str, bool* flag) {
        if (ImGui::MenuItem(str.c_str(), NULL, *flag)) {
            *flag = !(*flag);
        }
    };
    toggle_bool_item("mouse info"   , show_mouseinfo_pointer   );
    toggle_bool_item("isitem info"  , show_isiteminfo_pointer  );
    toggle_bool_item("rect info"    , show_rectinfo_pointer    );
    toggle_bool_item("demo window"  , show_demowindow_pointer  );
    toggle_bool_item("mesh window"  , show_meshwindow_pointer  );
    toggle_bool_item("object window", show_objectwindow_pointer);
    ImGui::Separator();
    toggle_bool_item("tool menu"    , show_toolmenu_pointer    );
    toggle_bool_item("show grid"    , show_grid_pointer        );
}

// ********************************************************************************
/// <summary>
/// メインメニューの表示
/// </summary>
/// <created>いのうえ,2021/03/17</created>
/// <changed>いのうえ,2021/03/17</changed>
// ********************************************************************************
void MainMenu::Show(void) {

    ImGui::BeginMainMenuBar(); {
        GuiWindowRect::GetInstance().Add(WindowKeyName::MainMenu);
        if (ImGui::BeginMenu("File")) {
            File();
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")) {
            Edit();
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View")) {
            View();
            ImGui::EndMenu();
        }
    }
    ImGui::EndMainMenuBar();
}
