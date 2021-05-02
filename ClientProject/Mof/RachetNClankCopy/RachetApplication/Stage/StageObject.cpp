#include "StageObject.h"

/// <summary>
/// �R���X�g���N�^
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
    , _geometry_boxes() 
{
    RefreshWorldMatrix();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
StageObject::~StageObject(void) {
}

/// <summary>
/// �L���t���O�̎擾
/// </summary>
/// <returns>�L���t���O</returns>
bool StageObject::IsEnable(void) const {
    return _enable;
}

/// <summary>
/// �����蔻��t���O�̎擾
/// </summary>
/// <returns>�����蔻��t���O</returns>
bool StageObject::IsCollisionEnable(void) const {
    return _collision_enable;
}

/// <summary>
/// ��ނ̎擾
/// </summary>
/// <returns>���</returns>
StageObjectType StageObject::GetType(void) const {
    return _type;
}

/// <summary>
/// ���O�̎擾
/// </summary>
/// <returns>���O</returns>
std::string StageObject::GetName(void) const {
    return _name;
}

/// <summary>
/// ���b�V���ԍ��̎擾
/// </summary>
/// <returns>���b�V���ԍ�</returns>
Vector3 StageObject::GetPosition(void) const {
    return _position;
}

/// <summary>
/// ���W�̎擾
/// </summary>
/// <returns>���W</returns>
Vector3 StageObject::GetScale(void) const {
    return _scale;
}

/// <summary>
/// �g��̎擾
/// </summary>
/// <returns>�g��</returns>
int StageObject::GetMeshNo(void) const {
    return _mesh_no;
}

/// <summary>
/// ��]�̎擾
/// </summary>
/// <returns>��]</returns>
Vector3 StageObject::GetRotate(void) const {
    return _rotate;
}

/// <summary>
/// ���[���h�}�g���N�X�̎擾
/// </summary>
/// <returns>���[���h�}�g���N�X</returns>
CMatrix44 StageObject::GetWorldMatrix(void) const {
    return _world_matrix;
}

Mof::CBoxAABB StageObject::GetGeometryBox(int index) const {
    return _geometry_boxes.at(index);
}

/// <summary>
/// �`��p�}�g���N�X�̍Čv�Z
/// </summary>
void StageObject::RefreshWorldMatrix(void) {
    CMatrix44 scale, rotate, trans;
    scale.Scaling(_scale);
    rotate.RotationZXY(_rotate);
    trans.Translation(_position);
    _world_matrix = scale * rotate * trans;
}

void StageObject::GenerateCollisionBox(const MeshArray& meshes) {
    auto mesh = meshes.at(_mesh_no);
    _geometry_boxes.clear();
    _geometry_boxes.reserve(mesh->GetGeometryCount());

    for (int i = 0, n = mesh->GetGeometryCount(); i < n; i++) {
        auto geometry = mesh->GetGeometry(i);
        auto default_matrix = geometry->GetMatrix();
        Mof::CMatrix44 mat = default_matrix * _world_matrix;
        geometry->SetMatrix(mat);

        Mof::CVector3 scale; mat.GetScaling(scale);
        Mof::CVector3 trans; mat.GetTranslation(trans);

        Mof::CBoxAABB box; geometry->CalculateAABB(box);
        box.Size.x *= scale.x; box.Size.y *= scale.y; box.Size.z *= scale.z;
        box.Position.x += trans.x; box.Position.y += trans.y; box.Position.z += trans.z;
        std::swap(box.Size.y, box.Size.z);
        _geometry_boxes.push_back(box);

        geometry->SetMatrix(default_matrix);
    } // for
}
void StageObject::SetEnable(bool b) {
    _enable = b;
}