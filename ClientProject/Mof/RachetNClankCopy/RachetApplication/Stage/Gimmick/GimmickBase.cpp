#include "GimmickBase.h"

GimmickBase::GimmickBase(bool enable, bool collision, StageObjectType type, std::string name, int mesh_no, Vector3 pos, Vector3 scale, Vector3 rotate)
    : StageObject(enable, collision, type, name, mesh_no, pos, scale, rotate) {
}

GimmickBase::~GimmickBase(void) {
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
