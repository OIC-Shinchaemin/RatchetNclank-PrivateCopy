#include "Stage.h"
#include "Parser/JsonStageParser.h"

void Stage::RenderObject(const StageObjectPtr& obj) {
    if (!obj->IsEnable()) {
        return;
    }
    const int mesh_no = obj->GetMeshNo();
    if (mesh_no < 0 || _mesh_array.size() <= mesh_no) {
        return;
    }
    _mesh_array[mesh_no]->Render(obj->GetWorldMatrix());
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
    parse_data.gimmick_array_pointer       = &_gimmick_array;
    parse_data.box_array_pointer           = &_woodbox_array;
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
    if (parser->Load(path, parse_data) != StageFileResult::Success) {
        return false;
    }

    return true;
}

/// <summary>
/// 初期化
/// </summary>
void Stage::Initialize(void) {
    for (const auto& object : _static_object_array) {
        object->GenerateCollisionVolume(_mesh_array);
    } // for

    for (const auto& gimmick : _gimmick_array) {
        gimmick->Initialize();
    }
    for (const auto& box : _woodbox_array) {
        box->Initialize();
        box->SetBoxArray(&_woodbox_array);
        box->SetObjectArray(&_static_object_array);
        box->SetMeshArray(&_mesh_array);
        if (box->GetType() == StageObjectType::BoxNanotech) {
            box->SetEnable(true);
        }
        _box_enable_array_prev.push_back(box->IsEnable());
    }
    _init_flag = true;
}

/// <summary>
/// 更新
/// </summary>
void Stage::Update(float delta) {
    const int box_enable_size = _woodbox_array.size();
    bool      box_break_flag  = false;
    for (int i = 0; i < box_enable_size; i++) {
        if (_box_enable_array_prev[i] != _woodbox_array[i]->IsEnable()) {
            box_break_flag = true;
            break;
        }
    }
    if (box_break_flag || _init_flag) {
        for (auto& it : _woodbox_array) {
            it->ActionStart();
        }
    }
    for (const auto& gimmick : _gimmick_array) {
        gimmick->Update(delta);
    }
    for (const auto& box : _woodbox_array) {
        box->Update(delta);
    }
    for (int i = 0; i < box_enable_size; i++) {
        _box_enable_array_prev[i] = _woodbox_array[i]->IsEnable();
    }

    if (_init_flag) {
        _init_flag = false;
    }
}

/// <summary>
/// 描画
/// </summary>
void Stage::Render(void) {
    for (const auto& obj : _static_object_array) {
        RenderObject(obj);
        //obj->DebugRender();
    }
    for (const auto& gimmick : _gimmick_array) {
        RenderObject(gimmick);
    }
    for (const auto& box : _woodbox_array) {
        RenderObject(box);
    }
}

/// <summary>
/// 解放
/// </summary>
void Stage::Release(void) {

    _woodbox_array.clear();
    _gimmick_array.clear();
    _enemy_spawn_array.clear();
    _static_object_array.clear();
    _box_enable_array_prev.clear();

    for (auto& it : _mesh_array) {
        if (it) {
            it->Release();
            it = nullptr;
        }
    }
    _mesh_array.clear();
}

MeshArray& Stage::GetMeshArray(void) {
    return _mesh_array;
}

StageObjectArray& Stage::GetStaticObjectArray(void) {
    return _static_object_array;
}

/// <summary>
/// 敵の出現位置配列の取得
/// </summary>
/// <returns>敵の出現位置配列</returns>
EnemySpawnArray& Stage::GetEnemySpawnArray(void) {
    return _enemy_spawn_array;
}

GimmickArray& Stage::GetGimmickArray(void) {
    return _gimmick_array;
}

WoodBoxArray& Stage::GetWoodBoxArray(void) {
    return _woodbox_array;
}
