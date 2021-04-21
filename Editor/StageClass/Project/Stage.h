#pragma once
#include "StageObject.h"
#include "GimmickBase.h"

// 名前の置き換え
using MeshPtr         = std::shared_ptr<CMeshContainer>;
using MeshArray       = std::vector<MeshPtr>;
// pair<builder_path, pos_data>
using EnemySpawnData  = std::pair<std::string, StageObjectPtr>;
using EnemySpawnArray = std::vector<EnemySpawnData>;

/// <summary>
/// ステージクラス
/// </summary>
class Stage {
private:

    //! 静的なステージメッシュの生成フラグ
    bool                _create_static_stage_mesh;

    //! 生成時の一時メッシュ置き場(解放処理のため保存)
    CMeshContainerArray _copy_tmp_array;

    //! ステージで使用するメッシュの配列
    MeshArray           _mesh_array;

    //! 静的なオブジェクトの配列
    StageObjectArray    _static_object_array;

    //! 敵の出現位置配列
    EnemySpawnArray     _enemy_spawn_array;

    //! ギミックの配列
    GimmickArray        _gimmick_array;

    /// <summary>
    /// 静的なステージメッシュの生成
    /// </summary>
    /// <returns>true : 生成, false : 未生成</returns>
    bool CreateStaticStageMesh(void);

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

    /// <summary>
    /// 静的なステージメッシュを生成したかのフラグ取得
    /// </summary>
    /// <returns>静的なステージメッシュを生成したかのフラグ</returns>
    bool IsCreateStaticStageMesh(void) const;

    /// <summary>
    /// 静的なステージメッシュの取得
    /// </summary>
    /// <returns>生成していない場合 nullptr が返る</returns>
    MeshPtr GetStaticStageMesh(void);

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
};

