#include "MeshComponent.h"

#include "MotionComponent.h"


my::MeshComponent::MeshComponent(int priority) :
    super(priority),
    _mesh(),
    _motion_com(),
    _is_show(true) {
}

my::MeshComponent::MeshComponent(const my::MeshComponent& obj) :
    super(obj._priority),
    _mesh(obj._mesh),
    _motion_com(),
    _is_show(obj._is_show) {
    super::_path = obj._path;
}

my::MeshComponent::~MeshComponent() {
}

void my::MeshComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
    const char* path = "path";

    _ASSERT_EXPR(param.HasMember(path), L"指定のパラメータがありません");
    _ASSERT_EXPR(param[path].IsString(), L"パラメータの指定された型でありません");

    //auto temp = super::GetResource<Mof::CMeshContainer>(param[path].GetString());
    //this->SetMesh(temp);
}

void my::MeshComponent::SetMesh(const std::shared_ptr<Mof::CMeshContainer>& ptr) {
    this->_mesh = ptr;
}

std::string my::MeshComponent::GetType(void) const {
    return "MeshComponent";
}

std::weak_ptr<Mof::CMeshContainer> my::MeshComponent::GetMesh(void) const {
    return this->_mesh;
}

bool my::MeshComponent::Initialize(void) {
    super::Initialize();
    _motion_com = super::GetOwner()->GetComponent<my::MotionComponent>();
    return true;
}

bool my::MeshComponent::Render(void) {
    if (!this->_is_show) {
        this->_is_show = true;
        return false;
    } // if

    if (auto r = _mesh.lock()) {
        Mof::CMatrix44 scale, rotate, translate;
        scale.Scaling(super::GetOwner()->GetScale(), scale);
        rotate.RotationZXY(super::GetOwner()->GetRotate());
        translate.Translation(super::GetOwner()->GetPosition(), translate);
        auto world = scale * rotate * translate;

        if (auto motion_com = _motion_com.lock()) {
            auto motion = motion_com->GetMotionData();
            motion->RefreshBoneMatrix(world);
            r->Render(motion);
        } // if
        else {
            r->Render(world);
        } // else
    } // if
    return true;
}

bool my::MeshComponent::DebugRender(void) {
    return true;
}

bool my::MeshComponent::Release(void) {
    super::Release();
    _mesh.reset();
    return true;
}

std::shared_ptr<my::Component> my::MeshComponent::Clone(void) {
    return std::make_shared<my::MeshComponent>(*this);
}

void my::MeshComponent::HideByCurrentFrame(void) {
    this->_is_show = false;
}