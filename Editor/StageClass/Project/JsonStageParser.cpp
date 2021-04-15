#include "JsonStageParser.h"
#include "My/Core/Utility.h"
#include "My/Core/Header.h"

/// <summary>
/// �t�@�C������X�e�[�W�f�[�^�ɕ�������
/// </summary>
/// <param name="path">�t�@�C���p�X</param>
/// <param name="out">�o�̓f�[�^</param>
/// <returns>StageFileResult_Success : ����, ����ȊO : error</returns>
StageFileResult JsonStageParser::Load(const std::string& path, ParseData& out) {

    // json�̃h�L�������g
    rapidjson::Document json_document;

    // �܂�json�t�@�C���𕪉�
    if (!ut::ParseJsonDocument(path.c_str(), json_document)) {
        return StageFileResult_Error_Open;
    }

    // �ȈՃA�N�Z�X�p
    MeshArray*        mesh_array          = out.mesh_array_pointer;
    StageObjectArray* static_object_array = out.static_object_array_pointer;
    EnemySpawnArray*  enemy_spawn_array   = out.enemy_spawn_array_pointer;
    
    // ���b�V�����X�g�̕���
    if (json_document.HasMember("mesh_list")) {
        // �ȈՃA�N�Z�X�p
        const auto& json_mesh_list = json_document["mesh_list"];
        const int   mesh_count     = json_mesh_list.Size();

        // ���b�V���̐������������m��
        mesh_array->reserve(mesh_count);

        for (int i = 0; i < mesh_count; i++) {
            // ���b�V���p�X�̎擾
            // ���݂̃J�����g�f�B���N�g����Resource�ł��邱�ƑO��
            std::string mesh_path = json_mesh_list[i].GetString();

            // ���b�V���̓ǂݍ���
            MeshPtr mesh_tmp = std::make_shared<CMeshContainer>();
            if (!mesh_tmp->Load(mesh_path.c_str())) {
                return StageFileResult_Error_MeshLoad;
            }
            mesh_array->push_back(std::move(mesh_tmp));
        }
    };

    // �ÓI�I�u�W�F�N�g���X�g�̕���
    if (json_document.HasMember("static_object_list")) {
        // �ȈՃA�N�Z�X�p
        const auto& json_static_object_list = json_document["static_object_list"];
        const int   object_count            = json_static_object_list.Size();

        // �I�u�W�F�N�g�̐������������m��
        static_object_array->reserve(object_count);

        for (int i = 0; i < object_count; i++) {

            // �ȈՃA�N�Z�X�p
            const auto& json_object_data = json_static_object_list[i];
            
            // �e�f�[�^�擾
            Vector3 position, rotation, scale;
            bool        enable      = json_object_data["enable"].GetBool();
            bool        collision   = json_object_data["collision"].GetBool();
            std::string object_name = json_object_data["object_name"].GetString();
            int         mesh_no     = json_object_data["mesh_no"].GetInt();
            position.x              = json_object_data["pos_x"].GetDouble();
            position.y              = json_object_data["pos_y"].GetDouble();
            position.z              = json_object_data["pos_z"].GetDouble();
            scale.x                 = json_object_data["scale_x"].GetDouble();
            scale.y                 = json_object_data["scale_y"].GetDouble();
            scale.z                 = json_object_data["scale_z"].GetDouble();
            rotation.x              = json_object_data["rotation_x"].GetDouble();
            rotation.y              = json_object_data["rotation_y"].GetDouble();
            rotation.z              = json_object_data["rotation_z"].GetDouble();

            // �I�u�W�F�N�g�f�[�^�̓o�^
            StageObjectPtr object_tmp = std::make_shared<StageObject>(
                enable, collision, StageObjectType_StaticObject,
                object_name, mesh_no, position, scale, rotation
                );
            static_object_array->push_back(std::move(object_tmp));
        }
    };

    // �G�����ʒu��񃊃X�g�̕���
    if (json_document.HasMember("enemy_spawn_list")) {
        // �ȈՃA�N�Z�X�p
        const auto& json_enemy_spawn_list = json_document["enemy_spawn_list"];
        const int   enemy_count           = json_enemy_spawn_list.Size();

        // �G�̐������������m��
        enemy_spawn_array->reserve(enemy_count);
        
        for (int i = 0; i < enemy_count; i++) {

            // �ȈՃA�N�Z�X�p
            const auto& json_enemy_data = json_enemy_spawn_list[i];

            Vector3 position;
            std::string builder_path = json_enemy_data["builder"].GetString();
            std::string name         = json_enemy_data["name"].GetString();
            position.x               = json_enemy_data["pos_x"].GetDouble();
            position.y               = json_enemy_data["pos_y"].GetDouble();
            position.z               = json_enemy_data["pos_z"].GetDouble();

            // �G�o���ʒu�f�[�^�̓o�^
            StageObjectPtr object_tmp = std::make_shared<StageObject>(
                true, false, StageObjectType_EnemySpawnPoint,
                name, -1, position
                );
            EnemySpawnData enemy_tmp(builder_path, std::move(object_tmp));
            enemy_spawn_array->push_back(std::move(enemy_tmp));
        }
    }

    return StageFileResult_Success;
}
