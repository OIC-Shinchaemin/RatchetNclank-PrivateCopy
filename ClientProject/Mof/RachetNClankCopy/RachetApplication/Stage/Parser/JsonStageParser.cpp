#include "JsonStageParser.h"

bool JsonStageParser::MeshListParse(rapidjson::Document& json, MeshArray* out) {
    // �ȈՃA�N�Z�X�p
    const auto& json_mesh_list = json["mesh_list"];
    const int   mesh_count     = json_mesh_list.Size();

    // ���b�V���̐������������m��
    out->reserve(mesh_count);

    for (int i = 0; i < mesh_count; i++) {
        // ���b�V���p�X�̎擾
        // ���݂̃J�����g�f�B���N�g����Resource�ł��邱�ƑO��
        std::string mesh_path = json_mesh_list[i].GetString();

        // ���b�V���̓ǂݍ���
        MeshPtr mesh_tmp = std::make_shared<CMeshContainer>();
        if (!mesh_tmp->Load(mesh_path.c_str())) {
            return false;
        }
        out->push_back(std::move(mesh_tmp));
    }
    return true;
}

bool JsonStageParser::StaticObjectListParse(rapidjson::Document& json, StageObjectArray* out) {
    // �ȈՃA�N�Z�X�p
    const auto& json_static_object_list = json["static_object_list"];
    const int   object_count            = json_static_object_list.Size();

    // �I�u�W�F�N�g�̐������������m��
    out->reserve(object_count);

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
            enable, collision, StageObjectType::StaticObject,
            object_name, mesh_no, position, scale, rotation
            );
        out->push_back(std::move(object_tmp));
    }
    return true;
}

bool JsonStageParser::EnemySpawnListParse(rapidjson::Document& json, EnemySpawnArray* out) {
    // �ȈՃA�N�Z�X�p
    const auto& json_enemy_spawn_list = json["enemy_spawn_list"];
    const int   enemy_count = json_enemy_spawn_list.Size();

    // �G�̐������������m��
    out->reserve(enemy_count);

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
            true, false, StageObjectType::EnemySpawnPoint,
            name, -1, position
            );
        EnemySpawnData enemy_tmp(builder_path, std::move(object_tmp));
        out->push_back(std::move(enemy_tmp));
    }
    return true;
}

bool JsonStageParser::GimmickObjectListParse(rapidjson::Document& json, GimmickArray* out) {
    // �ȈՃA�N�Z�X�p
    const auto& json_gimmick_list = json["gimmick_list"];
    const int   object_count      = json_gimmick_list.Size();

    // �I�u�W�F�N�g�̐������������m��
    out->reserve(object_count);

    for (int i = 0; i < object_count; i++) {

        // �ȈՃA�N�Z�X�p
        const auto& json_object_data = json_gimmick_list[i];

        // �e�f�[�^�擾
        Vector3 position, rotation, scale;
        StageObjectType type    = static_cast<StageObjectType>(json_object_data["type"].GetInt());
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
        GimmickPtr gimmick_tmp = CreateGimmick(type, json_object_data);
        gimmick_tmp->SetStageObjectData(enable, collision, type, object_name, mesh_no, position, scale, rotation);
        out->push_back(std::move(gimmick_tmp));
    }
    return true;
}

#include "../Gimmick/Elevator.h"
#include "../Gimmick/Bridge.h"
#include "../Gimmick/WoodBox.h"
#include "../Gimmick/MoveCloud.h"
GimmickPtr JsonStageParser::CreateGimmick(StageObjectType type, const rapidjson::Value& data) {
    GimmickPtr ptr = nullptr;
    switch (type) {
    case StageObjectType::Elevator:
    {
        Vector3 end;
        end.x         = data["end_pos_x"].GetDouble();
        end.y         = data["end_pos_y"].GetDouble();
        end.z         = data["end_pos_z"].GetDouble();
        float request = data["request"].GetDouble();
        ptr           = std::make_shared<Elevator>(end, request);
    } break;
    case StageObjectType::Bridge:
    {
        Vector3 start;
        start.x = data["start_pos_x"].GetDouble();
        start.y = data["start_pos_y"].GetDouble();
        start.z = data["start_pos_z"].GetDouble();
        Vector3 end;
        end.x = data["end_pos_x"].GetDouble();
        end.y = data["end_pos_y"].GetDouble();
        end.z = data["end_pos_z"].GetDouble();
        auto temp = std::make_shared<Bridge>(start);
        temp->SetEndPosition(end);
        ptr     = temp;
    } break;
    case StageObjectType::BoxBullet:
    case StageObjectType::BoxBolt:
    case StageObjectType::BoxNanotech:
    {
        ptr = std::make_shared<WoodBox>();
    }break;
    case StageObjectType::MoveCloud_Near:
    case StageObjectType::MoveCloud_Middle:
    case StageObjectType::MoveCloud_Far:
    {
        ptr = std::make_shared<MoveCloud>();
    }break;
    }
    return ptr;
}

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
        return StageFileResult::Error_Open;
    }

    // �ȈՃA�N�Z�X�p
    MeshArray*        mesh_array          = out.mesh_array_pointer;
    StageObjectArray* static_object_array = out.static_object_array_pointer;
    EnemySpawnArray*  enemy_spawn_array   = out.enemy_spawn_array_pointer;
    GimmickArray*     gimmick_array       = out.gimmick_array_pointer;
    WoodBoxArray*     box_array           = out.box_array_pointer;
    
    // ���b�V�����X�g�̕���
    if (json_document.HasMember("mesh_list")) {
        if (!MeshListParse(json_document, mesh_array)) {
            return StageFileResult::Error_MeshLoad;
        }
    };

    // �ÓI�I�u�W�F�N�g���X�g�̕���
    if (json_document.HasMember("static_object_list")) {
        StaticObjectListParse(json_document, static_object_array);
    };

    // �G�����ʒu��񃊃X�g�̕���
    if (json_document.HasMember("enemy_spawn_list")) {
        EnemySpawnListParse(json_document, enemy_spawn_array);
    }

    if (json_document.HasMember("gimmick_list")) {
        GimmickObjectListParse(json_document, gimmick_array);
    }

    for (GimmickArray::iterator it = gimmick_array->begin(); it != gimmick_array->end();) {
        StageObjectType type = (*it)->GetType();
        if (type == StageObjectType::BoxBullet ||
            type == StageObjectType::BoxBolt ||
            type == StageObjectType::BoxNanotech) {
            box_array->push_back(std::dynamic_pointer_cast<WoodBox>(*it));
            it = gimmick_array->erase(it);
            continue;
        }
        else {
            ++it;
        }
    }

    return StageFileResult::Success;
}
