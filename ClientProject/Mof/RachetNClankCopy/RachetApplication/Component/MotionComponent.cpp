#include "MotionComponent.h"

#include "MeshComponent.h"


my::MotionComponent::MotionComponent(int priority) :
    super(priority),
    _motion(),
    _motion_names(),
    _path() {
}

my::MotionComponent::MotionComponent(const MotionComponent& obj) :
    super(obj),
    _motion(),
    _motion_names(obj._motion_names),
    _path(obj._path) {
}

my::MotionComponent::~MotionComponent() {
}

void my::MotionComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
    const char* path = "path";

    _ASSERT_EXPR(param.HasMember(path), L"指定のパラメータがありません");
    _ASSERT_EXPR(param[path].IsString(), L"パラメータの指定された型でありません");

    auto temp = super::_resource_manager.lock()->Get<std::shared_ptr<my::MotionNames>>(param[path].GetString());
    _motion_names = temp;

}

std::string my::MotionComponent::GetType(void) const {
    return "MotionComponent";
}

const std::shared_ptr<my::MotionNames> my::MotionComponent::GetMotionInfoMap(void) const {
    if (auto info = _motion_names.lock()) {
        return info;
    } // if
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
    super::Activate();
    auto mesh_com = super::GetOwner()->GetComponent<my::MeshComponent>();
    if (auto mesh = mesh_com->GetMeshContainer()) {
        _motion = mesh->CreateMotionController();
    } // if
    return true;
}

bool my::MotionComponent::Update(float delta_time) {
    if (super::GetOwner()->InCameraRange()) {
        _motion->AddTimer(delta_time);
    } // if
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

bool my::MotionComponent::AddTimer(float time) {
    if (_motion) {
        return _motion->AddTimer(time);
    } // if
    return false;
}

bool my::MotionComponent::ChangeMotionByName(const char* name, float speed, bool loop, bool same) {
    if (_motion) {
        return _motion->ChangeMotionByName(name, speed, loop, same);
    } // if
    return false;
}