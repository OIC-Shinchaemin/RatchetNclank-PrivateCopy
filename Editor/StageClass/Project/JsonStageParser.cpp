#include "JsonStageParser.h"
#include "My/Core/Utility.h"
#include "My/Core/Header.h"

/// <summary>
/// ファイルからステージデータに分解する
/// </summary>
/// <param name="path">ファイルパス</param>
/// <param name="out">出力データ</param>
/// <returns>StageFileResult_Success : 成功, それ以外 : error</returns>
StageFileResult JsonStageParser::Load(const std::string& path, ParseData& out) {

    // jsonのドキュメント
    rapidjson::Document json_document;

    // まずjsonファイルを分解
    if (!ut::ParseJsonDocument(path.c_str(), json_document)) {
        return StageFileResult_Error_Open;
    }

    // 簡易アクセス用
    MeshArray*        mesh_array          = out.mesh_array_pointer;
    StageObjectArray* static_object_array = out.static_object_array_pointer;
    EnemySpawnArray*  enemy_spawn_array   = out.enemy_spawn_array_pointer;
    
    // メッシュリストの分解
    if (json_document.HasMember("mesh_list")) {
        // 簡易アクセス用
        const auto& json_mesh_list = json_document["mesh_list"];
        const int   mesh_count     = json_mesh_list.Size();

        // メッシュの数だけメモリ確保
        mesh_array->reserve(mesh_count);

        for (int i = 0; i < mesh_count; i++) {
            // メッシュパスの取得
            // 現在のカレントディレクトリがResourceであること前提
            std::string mesh_path = json_mesh_list[i].GetString();

            // メッシュの読み込み
            MeshPtr mesh_tmp = std::make_shared<CMeshContainer>();
            if (!mesh_tmp->Load(mesh_path.c_str())) {
                return StageFileResult_Error_MeshLoad;
            }
            mesh_array->push_back(std::move(mesh_tmp));
        }
    };

    // 静的オブジェクトリストの分解
    if (json_document.HasMember("static_object_list")) {
        // 簡易アクセス用
        const auto& json_static_object_list = json_document["static_object_list"];
        const int   object_count            = json_static_object_list.Size();

        // オブジェクトの数だけメモリ確保
        static_object_array->reserve(object_count);

        for (int i = 0; i < object_count; i++) {

            // 簡易アクセス用
            const auto& json_object_data = json_static_object_list[i];
            
            // 各データ取得
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

            // オブジェクトデータの登録
            StageObjectPtr object_tmp = std::make_shared<StageObject>(
                enable, collision, StageObjectType_StaticObject,
                object_name, mesh_no, position, scale, rotation
                );
            static_object_array->push_back(std::move(object_tmp));
        }
    };

    // 敵初期位置情報リストの分解
    if (json_document.HasMember("enemy_spawn_list")) {
        // 簡易アクセス用
        const auto& json_enemy_spawn_list = json_document["enemy_spawn_list"];
        const int   enemy_count           = json_enemy_spawn_list.Size();

        // 敵の数だけメモリ確保
        enemy_spawn_array->reserve(enemy_count);
        
        for (int i = 0; i < enemy_count; i++) {

            // 簡易アクセス用
            const auto& json_enemy_data = json_enemy_spawn_list[i];

            Vector3 position;
            std::string builder_path = json_enemy_data["builder"].GetString();
            std::string name         = json_enemy_data["name"].GetString();
            position.x               = json_enemy_data["pos_x"].GetDouble();
            position.y               = json_enemy_data["pos_y"].GetDouble();
            position.z               = json_enemy_data["pos_z"].GetDouble();

            // 敵出現位置データの登録
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
