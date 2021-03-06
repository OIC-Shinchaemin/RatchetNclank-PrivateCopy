#pragma once
#include <Mof.h>

#include <string>
#include <memory>

#include "StageDefine.h"

// 名前の置き換え
using MeshPtr   = std::shared_ptr<CMeshContainer>;
using MeshArray = std::vector<MeshPtr>;

/// <summary>
/// ステージオブジェクトクラス
/// </summary>
class StageObject : public std::enable_shared_from_this<StageObject> {
protected:

    //! オブジェクトの有効フラグ
    bool             _enable;

    //! 当たり判定の有効フラグ
    bool             _collision_enable;

    //! オブジェクトの種類
    StageObjectType  _type;

    //! オブジェクトの名前
    std::string      _name;

    //! メッシュ配列の何番目を使用しているか
    int              _mesh_no;

    //! ワールド座標
    Vector3          _position;
    
    //! 拡大
    Vector3          _scale;

    //! 回転
    Vector3          _rotate;

    //! 描画用ワールドマトリクス
    CMatrix44        _world_matrix;

    //! 衝突球
    std::vector<Mof::CSphere> _geometry_spheres;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    StageObject(bool enable = true, bool collision = true,
                StageObjectType type = StageObjectType::None, std::string name = "",
                int mesh_no = -1,
                Vector3 pos = Vector3(),
                Vector3 scale = Vector3(1, 1, 1),
                Vector3 rotate = Vector3());

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~StageObject(void);

    /// <summary>
    /// 有効フラグの取得
    /// </summary>
    /// <returns>有効フラグ</returns>
    bool IsEnable(void) const;

    /// <summary>
    /// 当たり判定フラグの取得
    /// </summary>
    /// <returns>当たり判定フラグ</returns>
    bool IsCollisionEnable(void) const;

    /// <summary>
    /// 種類の取得
    /// </summary>
    /// <returns>種類</returns>
    StageObjectType GetType(void) const;

    /// <summary>
    /// 名前の取得
    /// </summary>
    /// <returns>名前</returns>
    std::string GetName(void) const;

    /// <summary>
    /// メッシュ番号の取得
    /// </summary>
    /// <returns>メッシュ番号</returns>
    int GetMeshNo(void) const;

    /// <summary>
    /// 座標の取得
    /// </summary>
    /// <returns>座標</returns>
    Vector3 GetPosition(void) const;

    /// <summary>
    /// 拡大の取得
    /// </summary>
    /// <returns>拡大</returns>
    Vector3 GetScale(void) const;

    /// <summary>
    /// 回転の取得
    /// </summary>
    /// <returns>回転</returns>
    Vector3 GetRotate(void) const;

    /// <summary>
    /// ワールドマトリクスの取得
    /// </summary>
    /// <returns>ワールドマトリクス</returns>
    CMatrix44 GetWorldMatrix(void) const;

    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CSphere GetGeometrySphere(int index) const;

    /// <summary>
    /// 描画用マトリクスの再計算
    /// </summary>
    void RefreshWorldMatrix(void);

    /// <summary>
    /// 生成
    /// </summary>
    void GenerateCollisionVolume(const MeshArray& meshes);
    
    void SetEnable(bool b);

    void SetName(const std::string& name);

    void SetType(StageObjectType type);

    void SetMeshNo(int no);

    virtual void SetPosition(const Vector3& pos);

    /// <summary>
    /// デバッグ
    /// </summary>
    /// <param name=""></param>
    void DebugRender(void);
#ifdef   STAGEEDITOR
    virtual bool* GetEnablePointer(void);
    virtual bool* GetCollisionEnablePointer(void);
    virtual int* GetMeshNoPointer(void);
    virtual float* GetPositionPointer(void);
    virtual float* GetScalePointer(void);
    virtual float* GetRotationPointer(void);
#endif //STAGEEDITOR
};

// 置き換え
using StageObjectPtr   = std::shared_ptr<StageObject>;
using StageObjectArray = std::vector<StageObjectPtr>;