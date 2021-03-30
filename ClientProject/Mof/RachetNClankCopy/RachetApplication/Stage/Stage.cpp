#include "Stage.h"
#include "My/Core/Utility.h"
#include <filesystem>

bool Stage::Parse(const rapidjson::Document* buffer, MeshList* mesh_list, ObjectList* object_list) {

    // ファイル詳細
    // "mesh_list": [
    //     メッシュファイル相対パス
    // ],
    // "object_list": [
    //     {
    //         "object_name": オブジェクト名,
    //         "mesh_name": メッシュ名,
    //         "pos_x": 座標位置X  * 1000,
    //         "pos_y": 座標位置Y  * 1000,
    //         "pos_z": 座標位置Z  * 1000,
    //         "scale_x": 拡大率X  * 1000,
    //         "scale_y": 拡大率Y  * 1000,
    //         "scale_z": 拡大率Z  * 1000,
    //         "rotation_x": 回転X * 1000,
    //         "rotation_y": 回転Y * 1000,
    //         "rotation_z": 回転Z * 1000
    //     }
    // ]
    // EOF

    if (!(*buffer).HasMember("mesh_list")) {
        return false;
    };
    const auto& json_mesh_list = (*buffer)["mesh_list"];
    int         mesh_count     = json_mesh_list.Size();
    mesh_list->reserve(mesh_count);
    for (int i = 0; i < mesh_count; i++) {
        _ASSERT_EXPR(json_mesh_list[i].IsString(), L"NO STR");
        std::string mesh_path = json_mesh_list[i].GetString();
        std::string filename  = Stage::GetFileName(mesh_path);
        LoadMesh(mesh_path, mesh_path);
    }

    if (!(*buffer).HasMember("object_list")) {
        return false;
    };
    const auto& json_object_list = (*buffer)["object_list"];
    int         object_count     = json_object_list.Size();
    object_list->reserve(object_count);
    for (int i = 0; i < object_count; i++) {
        const auto& json_object_data = json_object_list[i];
        std::string object_name      = json_object_data["object_name"].GetString();
        std::string mesh_name        = json_object_data["mesh_name"].GetString();

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
        object_data.mesh_pointer = Stage::GetMeshPtr(mesh_name);
        object_data.position     = position;
        object_data.rotation     = rotation;
        object_data.scale        = scale;

        AddObjectData add_object_data;
        add_object_data.first  = &object_data;
        add_object_data.second = object_list;
        Stage::AddObject(std::move(&add_object_data));
    }
    return true;
}

bool Stage::LoadMap(rapidjson::Document* buffer_pointer, const std::string& map_file) {
    if (!ut::ParseJsonDocument(map_file.c_str(), *buffer_pointer)) {
        return false;
    }
    return true;
}

bool Stage::LoadMesh(const std::string& key, const std::string& mesh_file) {
    Stage::MeshPtr mesh_pointer = GetMeshPtr(key);
    if (mesh_pointer == nullptr) {
        Stage::MeshPtr mesh = std::make_shared<CMeshContainer>();
        if (!mesh->Load(mesh_file.c_str())) {
            return false;
        }
        _mesh_array.push_back(Stage::MeshData(key, mesh));
    }
    return true;
}

Stage::MeshPtr Stage::GetMeshPtr(const std::string& key) {
    Stage::MeshPtr mesh_pointer = nullptr;
    for (const auto& it : _mesh_array) {
        if (it.first != key) {
            continue;
        }
        mesh_pointer = it.second;
        break;
    }
    return mesh_pointer;
}

std::string Stage::GetFileName(const std::string& file) {
    std::string fullpath = ChangeFullPath(file);
    int         path_i   = fullpath.find_last_of("\\") + 1;
    int         ext_i    = fullpath.find_last_of(".");
    std::string filename = fullpath.substr(path_i, ext_i - path_i);
    return filename;
}

std::string Stage::GetExt(const std::string& file) {
    std::string ext    = file;
    int         length = ext.find_last_of('.');
    ext                = ext.substr(length);
    return ext;
}

std::string Stage::ChangeFullPath(const std::string& file) {
    return std::filesystem::absolute(file).string();
}

void Stage::AddObject(AddObjectData* data) {
    ObjectData* object_data = (*data).first;
    ObjectList* object_list = (*data).second;
    using list_iterator = ObjectList::iterator;
    // 登録する名前
    std::string name = object_data->name;
    // すでに名前があるかの検索関数
    std::function<list_iterator(std::string)> name_find =
        [&](std::string n) {
        return std::find_if(object_list->begin(), object_list->end(), [&](const ObjectData& v) { return v.name == n; });
    };
    // 名前がかぶった場合の番号
    int count = 1;
    for (list_iterator it = name_find(name); it != object_list->end(); count++) {
        name = object_data->name + std::to_string(count);
        it = name_find(name);
    }
    // データの登録
    ObjectData push_data = *object_data;
    push_data.name       = name;
    object_list->push_back(push_data);
}

void Stage::Initialize(void) {
    rapidjson::Document buffer;
    std::string file   = "stage/test.json";
    bool load_map_flag = LoadMap(&buffer, file);
    bool Parse_flag    = Parse(&buffer, &_mesh_array, &_object_array);
}

void Stage::Update(void) {
}

void Stage::Render(void) {

    for (const auto& it : _object_array) {
        if (it.mesh_pointer == nullptr) {
            continue;
        }
        CMatrix44 matrix_world;
        CMatrix44 position, scale, rotation;
        position.Translation(it.position);
        scale.Scaling(it.scale);
        rotation.RotationZXY(it.rotation);
        matrix_world = scale * rotation * position;
        it.mesh_pointer->Render(matrix_world);
    }
}

void Stage::Release(void) {
    for (auto& it : _object_array) {
        it.mesh_pointer = nullptr;
    }
    _object_array.clear();
    for (auto& it : _mesh_array) {
        it.second->Release();
    }
    _mesh_array.clear();
}
