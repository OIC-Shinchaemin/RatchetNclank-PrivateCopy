#include "Stage.h"
#include <filesystem>

bool Stage::Purse(const std::string* buffer, MeshList* mesh_list, ObjectList* object_list) {
    // ファイル詳細
    // メッシュ数                       ( 4 byte )
    // LOOP
    // メッシュファイル相対パスの長さ   ( 4 byte )
    // メッシュファイル相対パス         ( メッシュファイル相対パスの長さ byte )
    // LOOP END
    // オブジェクト数                   ( 4 byte )
    // LOOP
    // オブジェクト名の長さ             ( 4 byte )
    // オブジェクト名                   ( オブジェクト名の長さ byte )
    // メッシュ名の長さ                 ( 4 byte )
    // メッシュ名                       ( メッシュ名の長さ byte )
    // 座標位置X * 1000                 ( 4 byte )
    // 座標位置Y * 1000                 ( 4 byte )
    // 座標位置Z * 1000                 ( 4 byte )
    // 拡大率X   * 1000                 ( 4 byte )
    // 拡大率Y   * 1000                 ( 4 byte )
    // 拡大率Z   * 1000                 ( 4 byte )
    // 回転X     * 1000                 ( 4 byte )
    // 回転Y     * 1000                 ( 4 byte )
    // 回転Z     * 1000                 ( 4 byte )
    // LOOP END
    // EOF

    std::function<MofS32(int)> purse_s32 = [&](int n) {
        const unsigned char buff[4] = {
            static_cast<MofU8>(buffer->c_str()[n + 0]),
            static_cast<MofU8>(buffer->c_str()[n + 1]),
            static_cast<MofU8>(buffer->c_str()[n + 2]),
            static_cast<MofU8>(buffer->c_str()[n + 3]),
        };
        MofS32 s32 = (buff[3] << 24) | (buff[2] << 16) | (buff[1] << 8) | (buff[0]);
        return s32;
    };
    
    std::function<std::string(int, int)> purse_string = [&](int n, int count) {
        std::string buff = buffer->substr(n, count);
        return buff;
    };
    
    int buff_index = 0;
    
    int mesh_count = purse_s32(buff_index);
    buff_index    += sizeof(MofS32);
    
    for (int i = 0; i < mesh_count; i++) {
        int mesh_path_length  = purse_s32(buff_index);
        buff_index           += sizeof(MofS32);
        std::string mesh_path = purse_string(buff_index, mesh_path_length);
        buff_index           += mesh_path_length;
        std::string filename  = Stage::GetFileName(mesh_path);
        std::string ext       = Stage::GetExt(mesh_path);
        if (!LoadMesh(filename + ext, ChangeFullPath(mesh_path))) {
            return false;
        }
        MeshData mesh_data;
        mesh_data.first  = filename;
        mesh_data.second = GetMeshPtr(filename + ext);
        (*mesh_list).push_back(mesh_data);
    }

    int object_count = purse_s32(buff_index);
    buff_index      += sizeof(MofS32);

    for (int i = 0; i < object_count; i++) {
        
        int object_name_length  = purse_s32(buff_index);
        buff_index             += sizeof(MofS32);
        
        std::string object_name = purse_string(buff_index, object_name_length);
        buff_index             += object_name_length;
        
        int mesh_name_length    = purse_s32(buff_index);
        buff_index             += sizeof(MofS32);

        std::string mesh_name   = purse_string(buff_index, mesh_name_length);
        buff_index             += mesh_name_length;

        Vector3 position, rotation, scale;
        position.x  = purse_s32(buff_index) * 0.001f;
        buff_index += sizeof(MofS32);               
        position.y  = purse_s32(buff_index) * 0.001f;
        buff_index += sizeof(MofS32);               
        position.z  = purse_s32(buff_index) * 0.001f;
        buff_index += sizeof(MofS32);               
                                                    
        scale.x     = purse_s32(buff_index) * 0.001f;
        buff_index += sizeof(MofS32);               
        scale.y     = purse_s32(buff_index) * 0.001f;
        buff_index += sizeof(MofS32);               
        scale.z     = purse_s32(buff_index) * 0.001f;
        buff_index += sizeof(MofS32);               
                                                    
        rotation.x  = purse_s32(buff_index) * 0.001f;
        buff_index += sizeof(MofS32);               
        rotation.y  = purse_s32(buff_index) * 0.001f;
        buff_index += sizeof(MofS32);               
        rotation.z  = purse_s32(buff_index) * 0.001f;
        buff_index += sizeof(MofS32);

        ObjectData object_data;
        object_data.name         = object_name;
        object_data.mesh_pointer = Stage::GetMeshPtr(mesh_name);
        object_data.position     = position;
        object_data.rotation     = rotation;
        object_data.scale        = scale;

        AddObjectData add_object_data;
        add_object_data.first  = &object_data;
        add_object_data.second = object_list;
        Stage::AddObject(&add_object_data);
    }
    return true;
}

bool Stage::LoadMap(std::string* buffer_pointer, const std::string& map_file) {
    const std::string& file_name = map_file;
    std::string*       buffer    = buffer_pointer;

    std::ifstream input_stream;
    input_stream.open(file_name, std::ios::binary);

    if (!input_stream.is_open()) {
        return false;
    }

    std::stringstream bufferstream;

    bufferstream << input_stream.rdbuf();
    *buffer = bufferstream.str();

    input_stream.close();
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
    std::string buffer;
    std::string file         = "test.map";
    std::string current_path = std::filesystem::current_path().string();
    std::string last_path    = Stage::GetFileName(current_path);
    bool load_map_flag       = LoadMap(&buffer, file);
    bool purse_flag          = Purse(&buffer, &_mesh_array, &_object_array);
}

void Stage::Update(void) {
}

void Stage::Render(void) {

    for (const auto& it : _object_array) {
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
