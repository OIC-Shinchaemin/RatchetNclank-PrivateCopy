#include "Elevator.h"

Elevator::Elevator(Vector3 end, float request, bool enable, bool collision, StageObjectType type, std::string name, int mesh_no, Vector3 pos, Vector3 scale, Vector3 rotate)
    : GimmickBase(enable, collision, type, name, mesh_no, pos, scale, rotate)
    , _start_pos(pos)
    , _end_pos(end)
    , _request_time(request)
    , _now_timer(0.0f)
    , _start_flag(false)
    , _end_flag(false)
    , _preview_position(_start_pos)
    , _initial_position()
    , _first_initialized(false) {
}

Elevator::~Elevator(void) {
}

Mof::CVector3 Elevator::GetPreviewPosition(void) const {
    return this->_preview_position;
}

float Elevator::GetRequestTime(void) const {
    return this->_request_time;
}

Mof::CVector3 Elevator::GetMoveValue(void) const {
    return this->GetPosition() - this->GetPreviewPosition();
}

Mof::CSphere Elevator::GetStartPositionSphere(void) const {
    return Mof::CSphere(_start_pos, 20.0f);
}

Mof::CSphere Elevator::GetEndPositionSphere(void) const {
    return Mof::CSphere(_end_pos, 20.0f);
}

void Elevator::Initialize(void) {
    _now_timer = 0.0f;
    _start_pos = _position;
    _start_flag = false;
    _end_flag = false;
    if (!_first_initialized) {
        _initial_position = _position;
    } // if
    else {
        _position = _initial_position;
        _start_pos = _initial_position;
    } // else
    _preview_position = _start_pos;
    RefreshWorldMatrix();
    _first_initialized = true;
}

void Elevator::Update(float delta) {
    if (!_start_flag) {
        return;
    }
    if (_end_flag) {
        _now_timer -= delta;
    }
    else {
        _now_timer += delta;
    }
    const float t = std::clamp((_now_timer / _request_time), 0.0f, 1.0f);
    _preview_position = _position;
    _position = CVector3Utilities::Lerp(_start_pos, _end_pos, t);
    if (t == 1.0f && !_end_flag) {
        _start_flag = false;
        _end_flag = true;
    }
    if (t == 0.0f && _end_flag) {
        _start_flag = false;
        _end_flag = false;
    }
    RefreshWorldMatrix();
}

void Elevator::ActionStart(void) {
    if (!_start_flag) {
        _start_flag = true;
    }
}

bool Elevator::IsStart(void) const {
    return _start_flag;
}

Vector3 Elevator::GetEndPos(void) const {
    return _end_pos;
}

float Elevator::GetRequest(void) const {
    return _request_time;
}

void Elevator::SetPosition(const Vector3& pos) {
    StageObject::SetPosition(pos);
    _start_pos = pos;
}

void Elevator::SetStageObjectData(bool enable, bool collision, StageObjectType type, std::string name, int mesh_no, Vector3 pos, Vector3 scale, Vector3 rotate) {
    GimmickBase::SetStageObjectData(enable, collision, type, name, mesh_no, pos, scale, rotate);
    SetPosition(pos);
}

#ifdef STAGEEDITOR

float* Elevator::GetStartPosPointer(void) {
    return _start_pos.fv;
}

float* Elevator::GetEndPosPointer(void) {
    return _end_pos.fv;
}

float* Elevator::GetRequestPointer(void) {
    return &_request_time;
}

#endif//STAGEEDITOR
void Elevator::ReInitialize(void) {
}