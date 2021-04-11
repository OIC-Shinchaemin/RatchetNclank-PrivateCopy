#include "MotionComponent.h"

#include "MeshComponent.h"


my::MotionComponent::MotionComponent(int priority) :
    super(priority),
    _motion(),
    _motion_names() ,
    _path(){
}

my::MotionComponent::MotionComponent(const MotionComponent& obj) :
    super(obj._priority),
    _motion(),
    _motion_names(obj._motion_names) ,
    _path(obj._path){
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

Mof::LPMeshMotionController my::MotionComponent::GetMotionData(void) const {
    return this->_motion;
}

bool my::MotionComponent::IsEndMotion(void) const {
    return _motion->IsEndMotion();
}

bool my::MotionComponent::Initialize(void) {
    super::Initialize();
    super::Start();
    auto mesh_com = super::GetOwner()->GetComponent<my::MeshComponent>();
    if (auto mesh = mesh_com->GetMesh().lock()) {
        _motion = mesh->CreateMotionController();
    } // if

    for (int i = 0; i < _motion->GetMotionCount(); i++) {
        auto name = *_motion->GetMotion(i)->GetName();
        //std::cout << "name  = " << name << "\n";
    } // for
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

bool my::MotionComponent::ChangeMotionByName(const char* name, float speed, bool loop, bool same) {
    if (_motion) {
        return _motion->ChangeMotionByName(name, speed, loop, same);
    } // if
    return false;
}