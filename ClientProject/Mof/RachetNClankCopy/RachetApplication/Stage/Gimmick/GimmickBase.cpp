#include "GimmickBase.h"


GimmickBase::GimmickBase(bool enable, bool collision, StageObjectType type, std::string name, int mesh_no, Vector3 pos, Vector3 scale, Vector3 rotate)
    : StageObject(enable, collision, type, name, mesh_no, pos, scale, rotate) {
}

GimmickBase::~GimmickBase(void) {
}

Mof::CVector3 GimmickBase::GetPreviewPosition(void) const {
    return Mof::CVector3();
}

float GimmickBase::GetRequestTime(void) const {
    return 0.0f;
}

Mof::CVector3 GimmickBase::GetMoveValue(void) const {
    return Mof::CVector3();
}

Mof::CSphere GimmickBase::GetStartPositionSphere(void) const {
    return Mof::CSphere();
}

Mof::CSphere GimmickBase::GetEndPositionSphere(void) const {
    return Mof::CSphere();
}

void GimmickBase::ActionStart(void) {
}

bool GimmickBase::IsStart(void) const {
    return false;
}

void GimmickBase::SetStageObjectData(bool enable, bool collision, StageObjectType type, std::string name, int mesh_no, Vector3 pos, Vector3 scale, Vector3 rotate) {
    _enable           = enable;
    _collision_enable = collision;
    _type             = type;
    _name             = name;
    _mesh_no          = mesh_no;
    _position         = pos;
    _scale            = scale;
    _rotate           = rotate;
}

void GimmickBase::ReInitialize(void) {
}
