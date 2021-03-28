#include "SaveProject.h"
#include <ostream>
#include "FileDialog.h"
#include "ParameterMap.h"

// ********************************************************************************
/// <summary>
/// 
/// </summary>
/// <param name="any"></param>
/// <returns></returns>
/// <created>いのうえ,2021/03/21</created>
/// <changed>いのうえ,2021/03/21</changed>
// ********************************************************************************
bool SaveProject::Action(std::any any) {

    SaveData* save_data = std::any_cast<SaveData*>(any);
    if (save_data == nullptr) {
        return false; 
    }

    const std::string& file_name = std::get<0>(*save_data);
    const MeshList*    mesh_list = std::get<1>(*save_data);
    const ObjectList*  obj_list  = std::get<2>(*save_data);

    // バイナリ書き込み
    std::ofstream write_stream;
    std::string   resource_path = *ParameterMap<std::string>::GetInstance().Get("resource_path");
    write_stream.open(resource_path + "\\\\" + file_name, std::ios::binary);
    if (!write_stream.is_open()) {
        return false;
    }

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

    MofU32 mesh_count = mesh_list->size();
    write_stream.write((LPCMofChar)&mesh_count, sizeof(MofU32));
    for (const auto & it : *mesh_list) {
        // 書き出しデータ
        std::string resource_path    = *ParameterMap<std::string>::GetInstance().Get("resource_path");
        std::string full_path        = FileDialog::ChangeFullPath(it.second->GetName()->GetString());
        std::string relative_path    = FileDialog::ChangeRelativePath(full_path.c_str(), resource_path.c_str());
        MofU32      file_path_length = relative_path.length();
        LPCMofChar  path             = relative_path.c_str();
        // 各書き出し
        write_stream.write((LPCMofChar)&file_path_length, sizeof(MofU32));
        write_stream.write(path                         , sizeof(char) * file_path_length);
    }

    MofU32 object_count = obj_list->size();
    write_stream.write((LPCMofChar)&object_count, sizeof(MofU32));
    for (const auto& it : *obj_list) {
        // 書き出しデータ
        MofU32     object_name_length = it.name.length();
        LPCMofChar object_name        = it.name.c_str();
        MofU32     name_length        = it.mesh_pointer->GetName()->GetLength();
        LPCMofChar name               = it.mesh_pointer->GetName()->GetString();
        MofS32     position_x         = static_cast<MofS32>(it.position.x * 1000.0f);
        MofS32     position_y         = static_cast<MofS32>(it.position.y * 1000.0f);
        MofS32     position_z         = static_cast<MofS32>(it.position.z * 1000.0f);
        MofS32     scale_x            = static_cast<MofS32>(it.scale.x    * 1000.0f);
        MofS32     scale_y            = static_cast<MofS32>(it.scale.y    * 1000.0f);
        MofS32     scale_z            = static_cast<MofS32>(it.scale.z    * 1000.0f);
        MofS32     rotation_x         = static_cast<MofS32>(it.rotation.x * 1000.0f);
        MofS32     rotation_y         = static_cast<MofS32>(it.rotation.y * 1000.0f);
        MofS32     rotation_z         = static_cast<MofS32>(it.rotation.z * 1000.0f);
        // 各書き出し
        write_stream.write((LPCMofChar)&object_name_length, sizeof(MofU32));
        write_stream.write(object_name                    , sizeof(char) * object_name_length);
        write_stream.write((LPCMofChar)&name_length       , sizeof(MofU32));
        write_stream.write(name                           , sizeof(char) * name_length);
        write_stream.write((LPCMofChar)&position_x        , sizeof(MofS32));
        write_stream.write((LPCMofChar)&position_y        , sizeof(MofS32));
        write_stream.write((LPCMofChar)&position_z        , sizeof(MofS32));
        write_stream.write((LPCMofChar)&scale_x           , sizeof(MofS32));
        write_stream.write((LPCMofChar)&scale_y           , sizeof(MofS32));
        write_stream.write((LPCMofChar)&scale_z           , sizeof(MofS32));
        write_stream.write((LPCMofChar)&rotation_x        , sizeof(MofS32));
        write_stream.write((LPCMofChar)&rotation_y        , sizeof(MofS32));
        write_stream.write((LPCMofChar)&rotation_z        , sizeof(MofS32));
    }
    write_stream.close();

    return true;
}
