#include "WoodBox.h"
#include <iostream>
bool WoodBox::CollisionStage(void) {
    for (auto& it : *_object_array_pointer) {
        if (!it->IsEnable() || !it->IsCollisionEnable() || it->GetName() == GetName()) {
            continue;
        }
        const int mesh_no = it->GetMeshNo();
        if (_mesh_array_pointer->size() <= mesh_no || mesh_no < 0) {
            continue;
        }
        const float height = 1.0f;
        CRay3D down_ray(_position, Vector3(0, -1, 0));
        down_ray.Position.y += height;
        CMatrix44 matrix_inv;
        it->GetWorldMatrix().Inverse(matrix_inv);
        CVector3Utilities::TransformCoord (down_ray.Position , matrix_inv, down_ray.Position );
        CVector3Utilities::TransformNormal(down_ray.Direction, matrix_inv, down_ray.Direction);
        COLLISIONOUTGEOMETRY geo_out;
        const LPMeshContainer mesh = (*_mesh_array_pointer)[mesh_no].get();
        if (down_ray.CollisionMesh(mesh, geo_out)) {
            if (geo_out.d <= height) {
                _position.y += (height)-geo_out.d;
                RefreshWorldMatrix();
                _gravity = 0.0f;
                return true;
            }
        }
    }
    return false;
}

bool WoodBox::CollisionBox(WoodBoxPtr& box) {
    if (_box_array_pointer  == nullptr ||
        _mesh_array_pointer == nullptr ||
        _mesh_array_pointer->size() <= 0) {
        return false;
    }
    for (auto& it : *_box_array_pointer) {
        if (!it->IsEnable() || it->GetName() == GetName()) {
            continue;
        }
        const int mesh_no = it->GetMeshNo();
        if (_mesh_array_pointer->size() <= mesh_no || mesh_no < 0) {
            continue;
        }
        const float height = 1.0f;
        CRay3D down_ray(_position, Vector3(0, -1, 0));
        down_ray.Position.y += height;
        CMatrix44 matrix_inv;
        it->GetWorldMatrix().Inverse(matrix_inv);
        CVector3Utilities::TransformCoord (down_ray.Position , matrix_inv, down_ray.Position );
        CVector3Utilities::TransformNormal(down_ray.Direction, matrix_inv, down_ray.Direction);
        COLLISIONOUTGEOMETRY geo_out;
        const LPMeshContainer mesh = (*_mesh_array_pointer)[mesh_no].get();
        if (down_ray.CollisionMesh(mesh, geo_out)) {
            if (geo_out.d <= height) {
                _position.y += (height) - geo_out.d;
                RefreshWorldMatrix();
                box = it;
                _gravity = 0.0f;
                return true;
            }
        }
    }
    return false;
}

WoodBox::WoodBox(bool enable, bool collision, StageObjectType type, std::string name, int mesh_no, Vector3 pos, Vector3 scale, Vector3 rotate)
    : GimmickBase(enable, collision, type, name, mesh_no, pos, scale, rotate)
    , _action_flag(false)
    , _gravity(0.0f)
    , _start_pos(pos)
    , _box_array_pointer(nullptr)
    , _mesh_array_pointer(nullptr) {
}

WoodBox::~WoodBox(void) {
}

void WoodBox::Initialize(void) {
    _position = _start_pos;
    RefreshWorldMatrix();
}

void WoodBox::Update(float delta) {
    WoodBoxPtr hit_box   = nullptr;
    bool collision_stage = false;
    bool collision_box   = false;

    if (_action_flag) {
        _gravity    += 10.0f * delta;
        _gravity     = std::min<float>(_gravity, 5.0f);
        _position.y -= _gravity * delta;
        RefreshWorldMatrix();
        collision_stage = CollisionStage();
        collision_box   = CollisionBox(hit_box);
    }

    if (collision_box) {
        if (!hit_box->IsStart()) {
            _action_flag = false;
        }
    }
    if (collision_stage) {
        _action_flag = false;
    }
}

void WoodBox::ActionStart(void) {
    if (!_action_flag) {
        _action_flag = true;
        _gravity = 2.0f;
    }
}

bool WoodBox::IsStart(void) const {
    return _action_flag;
}

void WoodBox::SetStageObjectData(bool enable, bool collision, StageObjectType type, std::string name, int mesh_no, Vector3 pos, Vector3 scale, Vector3 rotate) {
    GimmickBase::SetStageObjectData(enable, collision, type, name, mesh_no, pos, scale, rotate);
    _start_pos = pos;
}

void WoodBox::SetBoxArray(WoodBoxArray* array_ptr) {
    _box_array_pointer = array_ptr;
}

void WoodBox::SetObjectArray(StageObjectArray* array_pointer) {
    _object_array_pointer = array_pointer;
}

void WoodBox::SetMeshArray(MeshArray* array_ptr) {
    _mesh_array_pointer = array_ptr;
}
