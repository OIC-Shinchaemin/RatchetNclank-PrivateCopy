#include "Elevator.h"

Elevator::Elevator(Vector3 end, float request, bool enable, bool collision, StageObjectType type, std::string name, int mesh_no, Vector3 pos, Vector3 scale, Vector3 rotate) 
    : GimmickBase(enable, collision, type, name, mesh_no, pos, scale, rotate)
    , _start_pos(pos)
    , _end_pos(end)
    , _request_time(request)
    , _now_timer(0.0f)
    , _start_flag(false)
    , _end_flag(false) {
}

Elevator::~Elevator(void) {
}

void Elevator::Initialize(void) {
    _now_timer  = 0.0f;
    _position   = _start_pos;
    _start_flag = false;
    _end_flag   = false;
    RefreshWorldMatrix();
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
    _position     = CVector3Utilities::Lerp(_start_pos, _end_pos, t);
    if (t == 1.0f && !_end_flag) {
        _start_flag = false;
        _end_flag   = true;
    }
    if (t == 0.0f && _end_flag) {
        _start_flag = false;
        _end_flag   = false;
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
