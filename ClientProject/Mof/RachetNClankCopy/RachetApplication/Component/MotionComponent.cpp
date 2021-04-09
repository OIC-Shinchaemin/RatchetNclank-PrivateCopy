#include "MotionComponent.h"

#include "MeshComponent.h"


void my::MotionComponent::GenerateMotionNames(void) {
//    _motion_names.emplace(my::MotionType::kIdleWait, "bse_wait_lp");
//    _motion_names.emplace(my::MotionType::kMoveRun, "mov_run_lp");
//    _motion_names.emplace(my::MotionType::kMoveTurn, "mov_run_lp");
}

my::MotionComponent::MotionComponent(int priority) :
    super(priority),
    _motion(),
    _motion_names() {
}

my::MotionComponent::MotionComponent(const MotionComponent& obj) :
    super(obj._priority),
    _motion(),
    _motion_names(obj._motion_names) {
}

my::MotionComponent::~MotionComponent() {
}

std::string my::MotionComponent::GetType(void) const {
    return "MotionComponent";
}

const char* my::MotionComponent::GetMotionName(const std::string& type) {
    // check contains
    /*
    auto it = _motion_names.find(type);
    if (it != _motion_names.end()) {
        return it->second.c_str();
    } // id
    */
    return nullptr;
}

Mof::LPMeshMotionController my::MotionComponent::GetMotionData(void) const {
    return this->_motion;
}

bool my::MotionComponent::IsEndMotion(void) const {
    return _motion->IsEndMotion();
}

bool my::MotionComponent::Initialize(void) {
    super::Initialize();
    auto mesh_com = super::GetOwner()->GetComponent<my::MeshComponent>();
    if (auto mesh = mesh_com->GetMesh().lock()) {
        _motion = mesh->CreateMotionController();
    } // if

    for (int i = 0; i < _motion->GetMotionCount(); i++) {
        auto name = *_motion->GetMotion(i)->GetName();
        std::cout << "name  = " << name << "\n";
    } // for

    this->GenerateMotionNames();
    return true;
}

bool my::MotionComponent::Update(float delta_time) {
    _motion->AddTimer(delta_time);
    return true;
}

bool my::MotionComponent::Release(void) {
    super::Release();
    ut::SafeDelete(_motion);
    return true;
}

std::shared_ptr<my::Component> my::MotionComponent::Clone(void) {
    return std::make_shared<my::MotionComponent>(*this);
}

bool my::MotionComponent::ChangeMotionByName(const char* name, bool loop, float speed, bool same) {
    if (_motion) {
        return _motion->ChangeMotionByName(name, speed, loop, same);
    } // if
    return false;
}