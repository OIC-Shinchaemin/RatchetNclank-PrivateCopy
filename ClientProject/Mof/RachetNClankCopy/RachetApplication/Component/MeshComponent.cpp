#include "MeshComponent.h"


rachet::MeshComponent::MeshComponent(int priority) :
    super(priority),
    _mesh(),
    _color() {
}

rachet::MeshComponent::MeshComponent(const rachet::MeshComponent& obj) :
    super(obj),
    _mesh(obj._mesh),
    _color(obj._color) {
}

rachet::MeshComponent::~MeshComponent() {
}

void rachet::MeshComponent::SetParam(const rapidjson::Value& param) {
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

void rachet::MeshComponent::SetMeshContainer(const std::shared_ptr<Mof::CMeshContainer>& ptr) {
    this->_mesh = ptr;
}

std::string rachet::MeshComponent::GetType(void) const {
    return "MeshComponent";
}

std::shared_ptr<Mof::CMeshContainer> rachet::MeshComponent::GetMeshContainer(void) const {
    return this->_mesh.lock();
}

Mof::CVector4 rachet::MeshComponent::GetColor(void) const {
    return this->_color;
}

bool rachet::MeshComponent::Render(void) {
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

bool rachet::MeshComponent::Release(void) {
    super::Release();
    _mesh.reset();
    return true;
}

std::shared_ptr<rachet::Component> rachet::MeshComponent::Clone(void) {
    return std::make_shared<rachet::MeshComponent>(*this);
}