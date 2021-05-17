#include "MeshComponent.h"

#include "MotionComponent.h"


my::MeshComponent::MeshComponent(int priority) :
    super(priority),
    _mesh(),
    _motion_com(),
    _color() {
}

my::MeshComponent::MeshComponent(const my::MeshComponent& obj) :
    super(obj),
    _mesh(obj._mesh),
    _motion_com(),
    _color(obj._color) {
    super::_path = obj._path;
}

my::MeshComponent::~MeshComponent() {
}

void my::MeshComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
    const char* path = "path";

    _ASSERT_EXPR(param.HasMember(path), L"指定のパラメータがありません");
    _ASSERT_EXPR(param[path].IsString(), L"パラメータの指定された型でありません");

    auto p = param[path].GetString();
    auto temp = super::_resource_manager.lock()->Get<std::shared_ptr<Mof::CMeshContainer>>(p);
    this->SetMesh(temp);

    const char* color = "color";
    if (param.HasMember(color)) {
        _ASSERT_EXPR(param[color].IsArray(), L"パラメータの指定された型でありません");
        for (int i = 0, n = param[color].GetArray().Size(); i < n; i++) {
            _color.fv[i] = param[color].GetArray()[i].GetFloat();
        } // for
    } // if
    else {
        _color = math::vec4::kOne;
    } // else
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
    if (!super::GetOwner()->InCameraRange()) {
        return false;
    } // if

    auto owner = super::GetOwner();
    // 描画
    if (auto r = _mesh.lock()) {
        Mof::CMatrix44 scale, rotate, translate;
        Mof::CQuaternion quat; quat.Rotation(owner->GetRotate());
        
        scale.Scaling(owner->GetScale(), scale);
        quat.ConvertMatrixTranspose(rotate);
        //rotate.RotationZXY(owner->GetRotate());
        translate.Translation(owner->GetPosition(), translate);

        Mof::CMatrix44 world = scale * rotate * translate;
        /*
        if (owner->GetParentTransform().has_value()) {
            auto parent = owner->GetParentTransform().value();
            world = world * parent;
        } // if
        */
        if (auto motion_com = _motion_com.lock()) {
            auto motion = motion_com->GetMotionData();
            motion->RefreshBoneMatrix(world);
            r->Render(motion, _color);
        } // if
        else {
            r->Render(world);
        } // else
    } // if
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