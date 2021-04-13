#include "ProjectDataPurse.h"
#include "Define.h"
#include "ActionManager.h"
#include "FileDialog.h"
#include "ActionKeyName.h"

// ********************************************************************************
/// <summary>
/// 
/// </summary>
/// <param name="any"></param>
/// <returns></returns>
/// <created>いのうえ,2021/03/26</created>
/// <changed>いのうえ,2021/03/26</changed>
// ********************************************************************************
bool ProjectDataPurse::Action(std::any any) {
    const SaveData* save_data = std::any_cast<SaveData*>(any);
    if (save_data == nullptr) {
        return false;
    }
    const std::string& project_data = std::get<0>(*save_data);
    MeshList*          mesh_list    = std::get<1>(*save_data);
    ObjectList*        object_list  = std::get<2>(*save_data);

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
            static_cast<MofU8>(project_data.c_str()[n + 0]),
            static_cast<MofU8>(project_data.c_str()[n + 1]),
            static_cast<MofU8>(project_data.c_str()[n + 2]),
            static_cast<MofU8>(project_data.c_str()[n + 3]),
        };
        MofS32 s32 = (buff[3] << 24) | (buff[2] << 16) | (buff[1] << 8) | (buff[0]);
        return s32;
    };
    
    std::function<std::string(int, int)> purse_string = [&](int n, int count) {
        std::string buff = project_data.substr(n, count);
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
        std::string filename  = FileDialog::GetFileName(mesh_path.c_str());
        std::string ext       = FileDialog::GetExt(mesh_path.c_str());
        std::pair<std::string, std::string> load_data(filename + ext, mesh_path);
        ActionManager::GetInstance().Action(ActionKeyName::MeshLoad, load_data);
        MeshData mesh_data;
        mesh_data.first  = filename;
        mesh_data.second = MeshAsset::GetAsset(filename + ext);
        (*mesh_list).push_back(mesh_data);
    }

    int object_count = purse_s32(buff_index);
    buff_index += sizeof(MofS32);

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
        object_data.mesh_pointer = MeshAsset::GetAsset(mesh_name);
        object_data.position     = position;
        object_data.rotation     = rotation;
        object_data.scale        = scale;

        AddObjectData add_object_data;
        add_object_data.first  = &object_data;
        add_object_data.second = object_list;
        ActionManager::GetInstance().Action(ActionKeyName::AddObject, &add_object_data);
    }
    return true;
}
