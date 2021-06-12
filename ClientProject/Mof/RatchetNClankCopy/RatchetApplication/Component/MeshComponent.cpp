#include "MeshComponent.h"


ratchet::component::MeshComponent::MeshComponent(int priority) :
    super(priority),
    _mesh(),
    _color() {
}

ratchet::component::MeshComponent::MeshComponent(const ratchet::component::MeshComponent& obj) :
    super(obj),
    _mesh(obj._mesh),
    _color(obj._color) {
}

ratchet::component::MeshComponent::~MeshComponent() {
}

void ratchet::component::MeshComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
    const char* path = "path";

    _ASSERT_EXPR(param.HasMember(path), L"指定のパラメータがありません");
    _ASSERT_EXPR(param[path].IsString(), L"パラメータの指定された型でありません");

    auto p = param[path].GetString();
    auto temp = super::_resource_manager.lock()->Get<std::shared_ptr<Mof::CMeshContainer>>(p);
    this->SetMeshContainer(temp);

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

void ratchet::component::MeshComponent::SetMeshContainer(const std::shared_ptr<Mof::CMeshContainer>& ptr) {
    this->_mesh = ptr;
}

std::string ratchet::component::MeshComponent::GetType(void) const {
    return "MeshComponent";
}

std::shared_ptr<Mof::CMeshContainer> ratchet::component::MeshComponent::GetMeshContainer(void) const {
    return this->_mesh.lock();
}

Mof::CVector4 ratchet::component::MeshComponent::GetColor(void) const {
    return this->_color;
}

bool ratchet::component::MeshComponent::Render(void) {
    if (!super::GetOwner()->InCameraRange()) {
        return false;
    } // if

    auto owner = super::GetOwner();
    // 描画
    if (auto mesh = this->GetMeshContainer(); mesh) {
        Mof::CMatrix44 scale, rotate, translate;
        Mof::CQuaternion quat; quat.Rotation(owner->GetRotate());

        scale.Scaling(owner->GetScale(), scale);
        quat.ConvertMatrixTranspose(rotate);
        translate.Translation(owner->GetPosition(), translate);

        Mof::CMatrix44 world = scale * rotate * translate;
        mesh->Render(world);
    } // if
    return true;
}

bool ratchet::component::MeshComponent::Release(void) {
    super::Release();
    _mesh.reset();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::MeshComponent::Clone(void) {
    return std::make_shared<ratchet::component::MeshComponent>(*this);
}