#include "ObjectWindow.h"
#include "WindowKeyName.h"
#include "GuiWindowRect.h"
#include "ParameterMap.h"
#include "ActionManager.h"
#include "ActionKeyName.h"

// ********************************************************************************
/// <summary>
/// オブジェクトリストの表示
/// </summary>
/// <created>いのうえ,2021/03/20</created>
/// <changed>いのうえ,2021/03/20</changed>
// ********************************************************************************
void ObjectWindow::ShowObjectList(void) {
    int size = _object_list.size();
    int i = 0;
    ImGui::BeginChild("object list", ImVec2(150, -ImGui::GetFrameHeightWithSpacing()), true);
    for (auto& it : _object_list) {
        if (ImGui::Selectable(it.name.c_str(), _object_list_current == i)) {
            _object_list_current = i;
            _object_select_item  = &it;
        }
        i++;
    }
    ImGui::EndChild();
}

// ********************************************************************************
/// <summary>
/// 選択中のオブジェクトデータ情報を表示
/// </summary>
/// <created>いのうえ,2021/03/20</created>
/// <changed>いのうえ,2021/03/20</changed>
// ********************************************************************************
void ObjectWindow::ShowObjectInfo(void) {
    ImGui::BeginGroup(); {
        // メッシュ情報関連の表示
        ImGui::BeginChild("object info", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()), true);
        // 選択中アイテムがある場合のみ表示する
        if (_object_select_item) {
            // ファイル名を表示する
            char object_name[128]    =  "";
            int  object_name_length  = 128;
            strcpy(object_name, _object_select_item->name.c_str());
            // 名前の表示と入力から変更できるようにする
            if (ImGui::InputText("object name", object_name, object_name_length)) {
                _object_select_item->name = object_name;
            };
            // 各ステータスをドラッグか直接入力するかで編集できるようにする
            ImGui::Text("input mode : "); ImGui::SameLine();
            if (ImGui::RadioButton("drag" ,  _object_data_input_mode)) { _object_data_input_mode =  true; } ImGui::SameLine();
            if (ImGui::RadioButton("input", !_object_data_input_mode)) { _object_data_input_mode = false; }
            if (_object_data_input_mode) {
                ImGui::DragFloat3("position", _object_select_item->position,           0.01f, MOF_FLOAT_MINF, MOF_FLOAT_INF);
                ImGui::DragFloat3("scale"   , _object_select_item->scale   ,           0.01f, MOF_FLOAT_MINF, MOF_FLOAT_INF);
                ImGui::DragFloat3("rotation", _object_select_item->rotation, MOF_ToRadian(1), MOF_FLOAT_MINF, MOF_FLOAT_INF);
            }
            else {
                ImGui::InputFloat3("position", _object_select_item->position);
                ImGui::InputFloat3("scale"   , _object_select_item->scale   );
                ImGui::InputFloat3("rotation", _object_select_item->rotation);
            }
            // ファイル名の表示
            ImGui::Text("file : %s", _object_select_item->mesh_pointer->GetName()->GetString());
            // データの破棄
            if (ImGui::Button("remove")) {
                Remove();
            }
        }
        ImGui::EndChild();
    }
    ImGui::EndGroup();
}

// ********************************************************************************
/// <summary>
/// データの破棄
/// </summary>
/// <created>いのうえ,2021/03/20</created>
/// <changed>いのうえ,2021/03/20</changed>
// ********************************************************************************
void ObjectWindow::Remove(void) {
    // 選択中のデータを参照する
    const ObjectData& delete_obj = *_object_select_item;
    // リストから削除
    _object_list.erase(
        std::find_if(_object_list.begin(), _object_list.end(),
            [&](const ObjectData& data) { return ObjectData::Compare(data, delete_obj); }
        )
    );
    // 選択中のデータを差し替えておく
    if (_object_list_current >= 0) {
        _object_select_item = &_object_list[_object_list_current];
    }
    else {
        _object_select_item = nullptr;
    }
}

// ********************************************************************************
/// <summary>
/// コンストラクタ
/// </summary>
/// <created>いのうえ,2021/03/20</created>
/// <changed>いのうえ,2021/03/20</changed>
// ********************************************************************************
ObjectWindow::ObjectWindow(void) {
    ParameterMap<ObjectList>::GetInstance().Set("object_list", &_object_list);
}

// ********************************************************************************
/// <summary>
/// デストラクタ
/// </summary>
/// <created>いのうえ,2021/03/20</created>
/// <changed>いのうえ,2021/03/20</changed>
// ********************************************************************************
ObjectWindow::~ObjectWindow(void) {
}

// ********************************************************************************
/// <summary>
/// ウィンドウの表示
/// </summary>
/// <created>いのうえ,2021/03/20</created>
/// <changed>いのうえ,2021/03/20</changed>
// ********************************************************************************
void ObjectWindow::Show(void) {
    ImGui::Begin("object window", ParameterMap<bool>::GetInstance().Get(WindowKeyName::ObjectWindow)); {
        GuiWindowRect::GetInstance().Add(WindowKeyName::ObjectWindow);
        // リストの表示
        ShowObjectList(); ImGui::SameLine();
        // 情報の表示
        ShowObjectInfo();
    }
    ImGui::End();
}

// ********************************************************************************
/// <summary>
/// オブジェクトデータの追加
/// </summary>
/// <param name="data">追加するデータ</param>
/// <created>いのうえ,2021/03/20</created>
/// <changed>いのうえ,2021/03/20</changed>
// ********************************************************************************
void ObjectWindow::Add(ObjectData& data) {
    AddObjectData object_data;
    object_data.first  = &data;
    object_data.second = &_object_list;
    ActionManager::GetInstance().Action(ActionKeyName::AddObject, &object_data);

    _object_list_current = static_cast<int>(_object_list.size() - 1);
    _object_select_item  = &(_object_list[_object_list_current]);

}

// ********************************************************************************
/// <summary>
/// 現在選択中のデータを取得する
/// </summary>
/// <returns>現在選択中のデータポインタ</returns>
/// <created>いのうえ,2021/03/20</created>
/// <changed>いのうえ,2021/03/20</changed>
// ********************************************************************************
ObjectData* ObjectWindow::GetSelectObjectData(void) {
    if (_object_select_item == nullptr && _object_list.size() > 0) {
        _object_select_item = &(_object_list[0]);
    }
    return _object_select_item;
}

// ********************************************************************************
/// <summary>
/// オブジェクトリストの取得
/// </summary>
/// <returns>オブジェクトリスト</returns>
/// <created>いのうえ,2021/03/20</created>
/// <changed>いのうえ,2021/03/20</changed>
// ********************************************************************************
const std::vector<ObjectData>& ObjectWindow::GetObjectList(void) const {
    return _object_list;
}
