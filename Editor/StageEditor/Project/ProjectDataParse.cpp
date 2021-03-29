#include "ProjectDataParse.h"
#include "Define.h"
#include "ActionManager.h"
#include "FileDialog.h"
#include "ActionKeyName.h"
#include "My/Core/Header.h"

// ********************************************************************************
/// <summary>
/// 
/// </summary>
/// <param name="any"></param>
/// <returns></returns>
/// <created>いのうえ,2021/03/26</created>
/// <changed>いのうえ,2021/03/26</changed>
// ********************************************************************************
bool ProjectDataParse::Action(std::any any) {
    const ParseData* save_data = std::any_cast<ParseData*>(any);
    if (save_data == nullptr) {
        return false;
    }
    const rapidjson::Document* project_data = std::get<0>(*save_data);
    MeshList*                  mesh_list    = std::get<1>(*save_data);
    ObjectList*                object_list  = std::get<2>(*save_data);

    // ファイル詳細
    // "mesh_list": [
    //     メッシュファイル相対パス
    // ],
    // "object_list": [
    //     "object_name": オブジェクト名,
    //     "mesh_name": メッシュ名,
    //     "pos_x": 座標位置X  * 1000,
    //     "pos_y": 座標位置Y  * 1000,
    //     "pos_z": 座標位置Z  * 1000,
    //     "scale_x": 拡大率X  * 1000,
    //     "scale_y": 拡大率Y  * 1000,
    //     "scale_z": 拡大率Z  * 1000,
    //     "rotation_x": 回転X * 1000,
    //     "rotation_y": 回転Y * 1000,
    //     "rotation_z": 回転Z * 1000
    // ]
    // EOF
    
    if (!(*project_data).HasMember("mesh_list")) {
        return false;
    };
    const auto& json_mesh_list = (*project_data)["mesh_list"];
    int mesh_count = json_mesh_list.Size();
    mesh_list->reserve(mesh_count);
    for (int i = 0; i < mesh_count; i++) {
        _ASSERT_EXPR(json_mesh_list[i].IsString(), L"NO STR");
        std::string mesh_path = json_mesh_list[i].GetString();
        std::string filename  = FileDialog::GetFileName(mesh_path.c_str());
        std::string ext       = FileDialog::GetExt(mesh_path.c_str());
        std::pair<std::string, std::string> load_data(filename + ext, mesh_path);
        ActionManager::GetInstance().Action(ActionKeyName::MeshLoad, load_data);
        MeshData mesh_data;
        mesh_data.first  = filename;
        mesh_data.second = MeshAsset::GetAsset(filename + ext);
        (*mesh_list).push_back(std::move(mesh_data));
    }

    if (!(*project_data).HasMember("object_list")) {
        return false;
    };
    const auto& json_object_list = (*project_data)["object_list"];
    int object_count = json_object_list.Size();
    object_list->reserve(object_count);
    for (int i = 0; i < object_count; i++) {
        const auto& json_object_data = json_object_list[i];
        std::string object_name = json_object_data["object_name"].GetString();
        std::string mesh_name   = json_object_data["mesh_name"].GetString();

        Vector3 position, rotation, scale;
        position.x  = json_object_data["pos_x"].GetInt() * 0.001f;
        position.y  = json_object_data["pos_y"].GetInt() * 0.001f;
        position.z  = json_object_data["pos_z"].GetInt() * 0.001f;
                                                    
        scale.x     = json_object_data["scale_x"].GetInt() * 0.001f;
        scale.y     = json_object_data["scale_y"].GetInt() * 0.001f;
        scale.z     = json_object_data["scale_z"].GetInt() * 0.001f;
                                                    
        rotation.x  = json_object_data["rotation_x"].GetInt() * 0.001f;
        rotation.y  = json_object_data["rotation_y"].GetInt() * 0.001f;
        rotation.z  = json_object_data["rotation_z"].GetInt() * 0.001f;

        ObjectData object_data;
        object_data.name         = object_name;
        object_data.mesh_pointer = MeshAsset::GetAsset(mesh_name);
        object_data.position     = position;
        object_data.rotation     = rotation;
        object_data.scale        = scale;

        AddObjectData add_object_data;
        add_object_data.first  = &object_data;
        add_object_data.second = object_list;
        ActionManager::GetInstance().Action(ActionKeyName::AddObject, std::move(&add_object_data));
    }
    return true;
}
