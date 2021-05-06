#include "Bridge.h"

Bridge::Bridge(Vector3 end, bool enable, bool collision, StageObjectType type, std::string name, int mesh_no, Vector3 pos, Vector3 scale, Vector3 rotate)
    : GimmickBase(enable, collision, type, name, mesh_no, pos, scale, rotate)
    , _start_pos(pos)
    , _end_pos(end)
    , _now_timer(0.0f)
    , _start_flag(false) {
}

Bridge::~Bridge(void) {
}

void Bridge::SetEndPosition(Mof::CVector3 pos) {
    this->_end_pos = pos;
}

Mof::CVector3 Bridge::GetPreviewPosition(void) const {
    return Mof::CVector3();
}

void Bridge::Initialize(void) {
    _now_timer  = 0.0f;
    _start_flag = false;
    _position   = _start_pos;
    RefreshWorldMatrix();
}

void Bridge::Update(float delta) {
    if (_start_flag) {
        _now_timer += delta;
    }
    const float t = std::clamp(_now_timer, 0.0f, 1.0f);
    _position     = CVector3Utilities::Lerp(_start_pos, _end_pos, t);
    RefreshWorldMatrix();
}

void Bridge::ActionStart(void) {
    _start_flag = true;
}

bool Bridge::IsStart(void) const {
    return _start_flag;
}

Vector3 Bridge::GetEndPos(void) const {
    return _end_pos;
}

void Bridge::SetPosition(const Vector3& pos) {
    StageObject::SetPosition(pos);
    _start_pos = pos;
}

void Bridge::SetStageObjectData(bool enable, bool collision, StageObjectType type, std::string name, int mesh_no, Vector3 pos, Vector3 scale, Vector3 rotate) {
    GimmickBase::SetStageObjectData(enable, collision, type, name, mesh_no, pos, scale, rotate);
    SetPosition(pos);
}

#ifdef STAGEEDITOR 

float* Bridge::GetStartPosPointer(void) {
    return _start_pos.fv;
}

float* Bridge::GetEndPosPointer(void) {
    return _end_pos.fv;
}

#endif //STAGEEDITOR