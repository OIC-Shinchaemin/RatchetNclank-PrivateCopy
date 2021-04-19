#include "Stage.h"
#include "JsonStageParser.h"

/// <summary>
/// 静的なステージメッシュの生成
/// </summary>
/// <returns>true : 生成, false : 未生成</returns>
bool Stage::CreateStaticStageMesh(void) {
    // 静的オブジェクトがなければ当たり判定用のメッシュは生成しない
    if (_static_object_array.size() <= 0) {
        return false;
    }
    // メッシュの生成
    MeshPtr stage_mesh = std::make_shared<CMeshContainer>();
    for (auto& object : _static_object_array) {
        // 万が一メッシュ登録していないオブジェクトがいれば弾く
        // 当たり判定の設定をしていないオブジェクトも弾く
        if (object->GetMeshNo() < 0 || !object->IsCollisionEnable()) {
            continue;
        }
        const int index = _copy_tmp_array.GetArrayCount();
        _copy_tmp_array.Add(_mesh_array[object->GetMeshNo()]->CreateCopyObject());
        LPMeshContainer mesh_tmp   = _copy_tmp_array[index];
        const int       mesh_count = mesh_tmp->GetMeshCount();
        for (int i = 0; i < mesh_count; i++) {
            // オブジェクトの拡大、回転に合わせてジオメトリの再計算
            const int geo_count = mesh_tmp->GetGeometryCount();
            for (int j = 0; j < geo_count; j++) {
                CMatrix44& matrix = mesh_tmp->GetMesh(i)->GetGeometry(j)->GetMatrix();
            
                // 現在のデータを取得
                CVector3 scale, rotate, trans;
                matrix.GetScaling(scale);
                matrix.GetRotation(rotate);
                matrix.GetTranslation(trans);

                // 再計算
                CMatrix44 scale_, rotate_, trans_;
                scale_.Scaling(scale * object->GetScale());
                trans_.Translation(trans * object->GetScale());
                rotate_.RotationZXY(object->GetRotate());
                trans_ *= rotate_;
                matrix  = scale_ * trans_;
            }
            // 再計算後のメッシュを登録
            stage_mesh->GetMesh()->Add(std::move(mesh_tmp->GetMesh(i)));
        }
    }
    // 静的オブジェクトがあっても一つも当たり判定を取らない場合メッシュの追加はしない
    if (stage_mesh->GetMesh()->GetArrayCount() <= 0) {
        return false;
    }
    // メッシュ配列の最後に追加する
    stage_mesh->SetName("static_stage_mesh");
    //stage_mesh->Save("static_stage_mesh.mom");
    _mesh_array.push_back(std::move(stage_mesh));
    return true;
}

/// <summary>
/// ステージの読み込み
/// </summary>
/// <param name="path">ステージデータファイルパス</param>
/// <returns>true : 成功, false : エラー</returns>
bool Stage::Load(const std::string& path) {
    // パーサーの準備
    ParseData parse_data;
    parse_data.mesh_array_pointer          = &_mesh_array;
    parse_data.static_object_array_pointer = &_static_object_array;
    parse_data.enemy_spawn_array_pointer   = &_enemy_spawn_array;
    StageParserPtr parser = nullptr;

    // 拡張子の取得
    int length      = path.find_last_of('.');
    std::string ext = path.substr(length);

    // パーサーの選択
    if (ext == ".json") {
        parser = std::make_shared<JsonStageParser>();
    }
    // パースできない拡張子
    else {
        return false;
    }

    // 読み込み
    if (parser->Load(path, parse_data) != TRUE) {
        return false;
    }

    // 静的オブジェクトの判定用メッシュ生成
    _create_static_stage_mesh = CreateStaticStageMesh();

    return true;
}

/// <summary>
/// 初期化
/// </summary>
void Stage::Initialize(void) {

}

/// <summary>
/// 更新
/// </summary>
void Stage::Update(void) {

}

/// <summary>
/// 描画
/// </summary>
void Stage::Render(void) {
    for (const auto& it : _static_object_array) {
        const int mesh_no = it->GetMeshNo();
        if (mesh_no < 0) {
            continue;
        }
        _mesh_array[mesh_no]->Render(it->GetWorldMatrix());
    }
}

/// <summary>
/// 解放
/// </summary>
void Stage::Release(void) {

    // 判定用メッシュの手動解放
    if (_create_static_stage_mesh) {
        for (int i = 0; i < _copy_tmp_array.GetArrayCount(); i++) {
            MOF_SAFE_DELETE(_copy_tmp_array[i]);
        }
        const int tail = (_mesh_array.size() - 1);
        for (int i = 0; i < _mesh_array[tail]->GetMeshCount(); i++) {
            _mesh_array[tail]->GetMesh()->SetData(nullptr, i);
        }
        _mesh_array[tail]->GetMesh()->ReSize(0);
        _mesh_array[tail] = nullptr;
    }

    for (auto& it : _mesh_array) {
        if (it) {
            it->Release();
            it = nullptr;
        }
    }
    _mesh_array.clear();
    _static_object_array.clear();
    _static_object_array.clear();
}

/// <summary>
/// 静的なステージメッシュを生成したかのフラグ取得
/// </summary>
/// <returns>静的なステージメッシュを生成したかのフラグ</returns>
bool Stage::IsCreateStaticStageMesh(void) const {
    return _create_static_stage_mesh;
}

/// <summary>
/// 静的なステージメッシュの取得
/// </summary>
/// <returns>生成していない場合 nullptr が返る</returns>
MeshPtr Stage::GetStaticStageMesh(void) {
    if (_create_static_stage_mesh) {
        return _mesh_array.back();
    }
    return nullptr;
}

/// <summary>
/// 敵の出現位置配列の取得
/// </summary>
/// <returns>敵の出現位置配列</returns>
EnemySpawnArray& Stage::GetEnemySpawnArray(void) {
    return _enemy_spawn_array;
}
