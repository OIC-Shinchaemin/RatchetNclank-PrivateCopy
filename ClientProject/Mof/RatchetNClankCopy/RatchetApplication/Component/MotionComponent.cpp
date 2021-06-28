#include "MotionComponent.h"

#include "MeshComponent.h"


ratchet::component::MotionComponent::MotionComponent(int priority) :
    super(priority),
    _motion(),
    _motion_names(),
    _path() {
}

ratchet::component::MotionComponent::MotionComponent(const MotionComponent& obj) :
    super(obj),
    _motion(),
    _motion_names(obj._motion_names),
    _path(obj._path) {
}

ratchet::component::MotionComponent::~MotionComponent() {
}

void ratchet::component::MotionComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
    const char* path = "path";

    _ASSERT_EXPR(param.HasMember(path), L"指定のパラメータがありません");
    _ASSERT_EXPR(param[path].IsString(), L"パラメータの指定された型でありません");

    auto temp = super::_resource_manager.lock()->Get<std::shared_ptr<ratchet::MotionNames>>(param[path].GetString());
    _motion_names = temp;

}

std::string ratchet::component::MotionComponent::GetType(void) const {
    return "MotionComponent";
}

const std::shared_ptr<ratchet::MotionNames> ratchet::component::MotionComponent::GetMotionInfoMap(void) const {
    if (auto info = _motion_names.lock()) {
        return info;
    } // if
    return nullptr;
}

Mof::LPMeshMotionController ratchet::component::MotionComponent::GetMotionData(void) const {
    return this->_motion;
}

bool ratchet::component::MotionComponent::IsEndMotion(void) const {
    return _motion->IsEndMotion();
}

bool ratchet::component::MotionComponent::Initialize(void) {
    super::Initialize();
    super::Activate();
    auto mesh_com = super::GetOwner()->GetComponent<ratchet::component::MeshComponent>();
    if (auto mesh = mesh_com->GetMeshContainer()) {
        _motion = mesh->CreateMotionController();
    } // if
    return true;
}

bool ratchet::component::MotionComponent::Update(float delta_time) {
    if (super::GetOwner()->InCameraRange()) {
        _motion->AddTimer(delta_time);
    } // if
    return true;
}

bool ratchet::component::MotionComponent::Release(void) {
    super::Release();
    ut::SafeDelete(_motion);
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::MotionComponent::Clone(void) {
    return std::make_shared<ratchet::component::MotionComponent>(*this);
}

bool ratchet::component::MotionComponent::AddTimer(float time) {
    if (_motion) {
        return _motion->AddTimer(time);
    } // if
    return false;
}

bool ratchet::component::MotionComponent::ChangeMotionByName(const char* name, float speed, bool loop, bool same) {
    if (_motion) {
        return _motion->ChangeMotionByName(name, speed, loop, same);
    } // if
    return false;
}