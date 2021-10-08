#pragma once
#include "StageObject.h"
#include "Gimmick/GimmickBase.h"
#include "Gimmick/WoodBox.h"
#include "Base/Core/Timer.h"


// pair<builder_path, pos_data>
using EnemySpawnData  = std::pair<std::string, StageObjectPtr>;
using EnemySpawnArray = std::vector<EnemySpawnData>;

/// <summary>
/// ステージクラス
/// </summary>
class Stage {
private:

    //! ステージで使用するメッシュの配列
    MeshArray           _mesh_array;

    //! 静的なオブジェクトの配列
    StageObjectArray    _static_object_array;

    //! 敵の出現位置配列
    EnemySpawnArray     _ENEMY_spawn_array;

    //! ギミックの配列
    GimmickArray        _gimmick_array;

    //! 箱系オブジェクトの配列
    WoodBoxArray        _woodbox_array;

    std::vector<bool>   _box_enable_array_prev;

    bool                _init_flag;

    //! 
    base::core::Timer _cursor_active_timer;
    //! 
    base::core::Timer _cursor_blinking_timer;
    //! カーソルテクスチャ
    Mof::CTexture _cursor_texture;

    void RenderObject(const StageObjectPtr& obj);

public:

    /// <summary>
    /// ステージの読み込み
    /// </summary>
    /// <param name="path">ステージデータファイルパス</param>
    /// <returns>true : 成功, false : エラー</returns>
    bool Load(const std::string& path);

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize(void);

    /// <summary>
    /// 更新
    /// </summary>
    void Update(float delta);

    /// <summary>
    /// 描画
    /// </summary>
    void Render(void);

    /// <summary>
    /// 解放
    /// </summary>
    void Release(void);

    MeshArray& GetMeshArray(void);

    StageObjectArray& GetStaticObjectArray(void);

    /// <summary>
    /// 敵の出現位置配列の取得
    /// </summary>
    /// <returns>敵の出現位置配列</returns>
    EnemySpawnArray& GetEnemySpawnArray(void);

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    GimmickArray& GetGimmickArray(void);

    WoodBoxArray& GetWoodBoxArray(void);
};

