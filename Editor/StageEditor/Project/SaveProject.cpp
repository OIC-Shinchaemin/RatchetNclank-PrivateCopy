#include "SaveProject.h"
#include <ostream>
#include "FileDialog.h"
#include "ParameterMap.h"

#include "My/Core/Header.h"
#include "rapidjson/prettywriter.h"

// ********************************************************************************
/// <summary>
/// 
/// </summary>
/// <param name="any"></param>
/// <returns></returns>
/// <created>���̂���,2021/03/21</created>
/// <changed>���̂���,2021/03/21</changed>
// ********************************************************************************
bool SaveProject::Action(std::any any) {

    SaveData* save_data = std::any_cast<SaveData*>(any);
    if (save_data == nullptr) {
        return false; 
    }

    const std::string& file_name = std::get<0>(*save_data);
    const MeshList*    mesh_list = std::get<1>(*save_data);
    const ObjectList*  obj_list  = std::get<2>(*save_data);

    rapidjson::Document document(rapidjson::Type::kObjectType);

    // �t�@�C���ڍ�
    // "mesh_list": [
    //     ���b�V���t�@�C�����΃p�X
    // ],
    // "object_list": [
    //     "object_name": �I�u�W�F�N�g��,
    //     "mesh_name": ���b�V����,
    //     "pos_x": ���W�ʒuX  * 1000,
    //     "pos_y": ���W�ʒuY  * 1000,
    //     "pos_z": ���W�ʒuZ  * 1000,
    //     "scale_x": �g�嗦X  * 1000,
    //     "scale_y": �g�嗦Y  * 1000,
    //     "scale_z": �g�嗦Z  * 1000,
    //     "rotation_x": ��]X * 1000,
    //     "rotation_y": ��]Y * 1000,
    //     "rotation_z": ��]Z * 1000
    // ]
    // EOF

    rapidjson::Value mesh_array(rapidjson::Type::kArrayType);
    for (const auto & it : *mesh_list) {
        // �����o���f�[�^
        std::string      resource_path    = *ParameterMap<std::string>::GetInstance().Get("resource_path");
        std::string      full_path        = FileDialog::ChangeFullPath(it.second->GetName()->GetString());
        CString          relative_path    = FileDialog::ChangeRelativePath(full_path.c_str(), resource_path.c_str()).c_str();
        // �e�����o��
        mesh_array.PushBack(
            rapidjson::Value().SetString(relative_path.GetString(), document.GetAllocator()),
            document.GetAllocator()
        );
    }

    document.AddMember("mesh_list", mesh_array, document.GetAllocator());

    rapidjson::Value object_array(rapidjson::Type::kArrayType);

    for (const auto& it : *obj_list) {
        // �����o���f�[�^
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
        
        // �e�����o��
        rapidjson::Value write_object(rapidjson::Type::kObjectType);
        auto write_object_name = rapidjson::StringRef(object_name, object_name_length);
        auto write_mesh_name   = rapidjson::StringRef(name       , name_length       );
        rapidjson::Value write_position_x(position_x);
        rapidjson::Value write_position_y(position_y);
        rapidjson::Value write_position_z(position_z);
        rapidjson::Value write_scale_x   (scale_x   );
        rapidjson::Value write_scale_y   (scale_y   );
        rapidjson::Value write_scale_z   (scale_z   );
        rapidjson::Value write_rotation_x(rotation_x);
        rapidjson::Value write_rotation_y(rotation_y);
        rapidjson::Value write_rotation_z(rotation_z);
        write_object.AddMember("object_name", write_object_name, document.GetAllocator());
        write_object.AddMember("mesh_name"  , write_mesh_name  , document.GetAllocator());
        write_object.AddMember("pos_x"      , write_position_x , document.GetAllocator());
        write_object.AddMember("pos_y"      , write_position_y , document.GetAllocator());
        write_object.AddMember("pos_z"      , write_position_z , document.GetAllocator());
        write_object.AddMember("scale_x"    , write_scale_x    , document.GetAllocator());
        write_object.AddMember("scale_y"    , write_scale_y    , document.GetAllocator());
        write_object.AddMember("scale_z"    , write_scale_z    , document.GetAllocator());
        write_object.AddMember("rotation_x" , write_rotation_x , document.GetAllocator());
        write_object.AddMember("rotation_y" , write_rotation_y , document.GetAllocator());
        write_object.AddMember("rotation_z" , write_rotation_z , document.GetAllocator());
        object_array.PushBack(write_object, document.GetAllocator());
    }

    document.AddMember("object_list", object_array, document.GetAllocator());

    // json��������
    std::ofstream write_stream;
    std::string   resource_path = *ParameterMap<std::string>::GetInstance().Get("resource_path");
    write_stream.open(resource_path + "\\" + file_name, std::ios::binary);
    if (!write_stream.is_open()) {
        return false;
    }
    rapidjson::OStreamWrapper stream(write_stream);
    rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(stream);
    document.Accept(writer);
    write_stream.close();

    return true;
}
