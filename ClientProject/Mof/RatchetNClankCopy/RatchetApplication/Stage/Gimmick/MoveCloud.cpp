#include "MoveCloud.h"

MoveCloud::MoveCloud(bool enable, bool collision, StageObjectType type, std::string name, int mesh_no, Vector3 pos, Vector3 scale, Vector3 rotate) 
    : GimmickBase(enable, collision, type, name, mesh_no, pos, scale, rotate)
    , _speed(0.0f) {
}

MoveCloud::~MoveCloud(void) {
}

void MoveCloud::Initialize(void) {
    switch (_type) {
    case StageObjectType::MoveCloud_Near:
        _speed = 3.0f;
        break;
    case StageObjectType::MoveCloud_Middle:
        _speed = 2.0f;
        break;
    case StageObjectType::MoveCloud_Far:
        _speed = 1.0f;
        break;
    }
}

void MoveCloud::Update(float delta) {
    _rotate.y += MOF_ToRadian(_speed) * delta;
    RefreshWorldMatrix();
}

bool MoveCloud::IsStart(void) const {
    return true;
}
