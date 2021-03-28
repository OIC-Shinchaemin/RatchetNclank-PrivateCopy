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

    // �o�C�i����������
    std::ofstream write_stream;
    std::string   resource_path = *ParameterMap<std::string>::GetInstance().Get("resource_path");
    write_stream.open(resource_path + "\\\\" + file_name, std::ios::binary);
    if (!write_stream.is_open()) {
        return false;
    }

    // �t�@�C���ڍ�
    // ���b�V����                       ( 4 byte )
    // LOOP
    // ���b�V���t�@�C�����΃p�X�̒���   ( 4 byte )
    // ���b�V���t�@�C�����΃p�X         ( ���b�V���t�@�C�����΃p�X�̒��� byte )
    // LOOP END
    // �I�u�W�F�N�g��                   ( 4 byte )
    // LOOP
    // �I�u�W�F�N�g���̒���             ( 4 byte )
    // �I�u�W�F�N�g��                   ( �I�u�W�F�N�g���̒��� byte )
    // ���b�V�����̒���                 ( 4 byte )
    // ���b�V����                       ( ���b�V�����̒��� byte )
    // ���W�ʒuX * 1000                 ( 4 byte )
    // ���W�ʒuY * 1000                 ( 4 byte )
    // ���W�ʒuZ * 1000                 ( 4 byte )
    // �g�嗦X   * 1000                 ( 4 byte )
    // �g�嗦Y   * 1000                 ( 4 byte )
    // �g�嗦Z   * 1000                 ( 4 byte )
    // ��]X     * 1000                 ( 4 byte )
    // ��]Y     * 1000                 ( 4 byte )
    // ��]Z     * 1000                 ( 4 byte )
    // LOOP END
    // EOF

    MofU32 mesh_count = mesh_list->size();
    write_stream.write((LPCMofChar)&mesh_count, sizeof(MofU32));
    for (const auto & it : *mesh_list) {
        // �����o���f�[�^
        std::string resource_path    = *ParameterMap<std::string>::GetInstance().Get("resource_path");
        std::string full_path        = FileDialog::ChangeFullPath(it.second->GetName()->GetString());
        std::string relative_path    = FileDialog::ChangeRelativePath(full_path.c_str(), resource_path.c_str());
        MofU32      file_path_length = relative_path.length();
        LPCMofChar  path             = relative_path.c_str();
        // �e�����o��
        write_stream.write((LPCMofChar)&file_path_length, sizeof(MofU32));
        write_stream.write(path                         , sizeof(char) * file_path_length);
    }

    MofU32 object_count = obj_list->size();
    write_stream.write((LPCMofChar)&object_count, sizeof(MofU32));
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
