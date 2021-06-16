#include "StageObject.h"

#include "Base/Core/Math.h"


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
    , _world_matrix()
    , _geometry_spheres() {
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

Mof::CSphere StageObject::GetGeometrySphere(int index) const {
    return _geometry_spheres.at(index);
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

void StageObject::GenerateCollisionVolume(const MeshArray& meshes) {
    auto mesh = meshes.at(_mesh_no);
    _geometry_spheres.clear();
    _geometry_spheres.reserve(mesh->GetGeometryCount());

    for (int i = 0, n = mesh->GetGeometryCount(); i < n; i++) {
        auto geometry = mesh->GetGeometry(i);
        auto default_matrix = geometry->GetMatrix();
        Mof::CMatrix44 mat = default_matrix * _world_matrix;
        geometry->SetMatrix(mat);

        Mof::CVector3 scale; mat.GetScaling(scale);
        Mof::CVector3 rotate; mat.GetRotation(rotate);
        Mof::CVector3 trans; mat.GetTranslation(trans);
        rotate.x -= math::kPi;
        rotate.y -= math::kPi;
        rotate.z -= math::kPi;
        trans.RotateAround(trans, rotate);

        Mof::CSphere sphere; geometry->CalculateSphere(sphere);
        sphere.r *= scale.x; 
        sphere.Position.x += trans.x; sphere.Position.y += trans.y; sphere.Position.z += trans.z;

        _geometry_spheres.push_back(sphere);
        geometry->SetMatrix(default_matrix);
    } // for
}

void StageObject::SetEnable(bool b) {
    _enable = b;
}

void StageObject::SetName(const std::string& name) {
    _name = name;
}

void StageObject::SetType(StageObjectType type) {
    _type = type;
}

void StageObject::SetMeshNo(int no) {
    _mesh_no = no;
}

void StageObject::SetPosition(const Vector3& pos) {
    _position = pos;
}

void StageObject::DebugRender(void) {
    for (auto volume: _geometry_spheres) {
        if (this->IsCollisionEnable()) {
            //::CGraphicsUtilities::RenderBox(box, Mof::CVector4(1.0f, 0.0f, 0.0f, 0.5f));
            ::CGraphicsUtilities::RenderLineSphere(volume, Mof::CVector4(1.0f, 0.0f, 0.0f, 0.5f));
        } // if
    } // for
}

#ifdef   STAGEEDITOR
bool* StageObject::GetEnablePointer(void) {
    return &_enable;
}
bool* StageObject::GetCollisionEnablePointer(void) {
    return &_collision_enable;
}
int* StageObject::GetMeshNoPointer(void) {
    return &_mesh_no;
}
float* StageObject::GetPositionPointer(void) {
    return _position.fv;
}

float* StageObject::GetScalePointer(void) {
    return _scale.fv;
}

float* StageObject::GetRotationPointer(void) {
    return _rotate.fv;
}
#endif //STAGEEDITOR