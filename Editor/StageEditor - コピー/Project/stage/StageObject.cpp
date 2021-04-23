#include "StageObject.h"

/// <summary>
/// コンストラクタ
/// </summary>
StageObject::StageObject(bool enable, bool collision, StageObjectType type, std::string name, int mesh_no, Vector3 pos, Vector3 scale, Vector3 rotate)
    : _enable(enable)
    , _collision_enable(collision)
    , _type(type)
    , _name(name)
    , _mesh_no(mesh_no)
    , _position(pos)
    , _scale(scale)
    , _rotate(rotate)
    , _world_matrix() {
    RefreshWorldMatrix();
}

/// <summary>
/// デストラクタ
/// </summary>
StageObject::~StageObject(void) {
}

/// <summary>
/// 有効フラグの取得
/// </summary>
/// <returns>有効フラグ</returns>
bool StageObject::IsEnable(void) const {
    return _enable;
}

/// <summary>
/// 当たり判定フラグの取得
/// </summary>
/// <returns>当たり判定フラグ</returns>
bool StageObject::IsCollisionEnable(void) const {
    return _collision_enable;
}

/// <summary>
/// 種類の取得
/// </summary>
/// <returns>種類</returns>
StageObjectType StageObject::GetType(void) const {
    return _type;
}

/// <summary>
/// 名前の取得
/// </summary>
/// <returns>名前</returns>
std::string StageObject::GetName(void) const {
    return _name;
}

/// <summary>
/// メッシュ番号の取得
/// </summary>
/// <returns>メッシュ番号</returns>
Vector3 StageObject::GetPosition(void) const {
    return _position;
}

/// <summary>
/// 座標の取得
/// </summary>
/// <returns>座標</returns>
Vector3 StageObject::GetScale(void) const {
    return _scale;
}

/// <summary>
/// 拡大の取得
/// </summary>
/// <returns>拡大</returns>
int StageObject::GetMeshNo(void) const {
    return _mesh_no;
}

/// <summary>
/// 回転の取得
/// </summary>
/// <returns>回転</returns>
Vector3 StageObject::GetRotate(void) const {
    return _rotate;
}

/// <summary>
/// ワールドマトリクスの取得
/// </summary>
/// <returns>ワールドマトリクス</returns>
CMatrix44 StageObject::GetWorldMatrix(void) const {
    return _world_matrix;
}

/// <summary>
/// 描画用マトリクスの再計算
/// </summary>
void StageObject::RefreshWorldMatrix(void) {
    CMatrix44 scale, rotate, trans;
    scale.Scaling(_scale);
    rotate.RotationZXY(_rotate);
    trans.Translation(_position);
    _world_matrix = scale * rotate * trans;
}

void StageObject::SetEnable(bool b) {
    _enable = b;
}