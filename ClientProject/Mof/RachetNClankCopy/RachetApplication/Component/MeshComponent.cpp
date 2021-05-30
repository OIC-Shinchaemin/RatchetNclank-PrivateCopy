#include "MeshComponent.h"


my::MeshComponent::MeshComponent(int priority) :
    super(priority),
    _mesh(),
    _color() {
}

my::MeshComponent::MeshComponent(const my::MeshComponent& obj) :
    super(obj),
    _mesh(obj._mesh),
    _color(obj._color) {
}

my::MeshComponent::~MeshComponent() {
}

void my::MeshComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
    const char* path = "path";

    _ASSERT_EXPR(param.HasMember(path), L"�w��̃p�����[�^������܂���");
    _ASSERT_EXPR(param[path].IsString(), L"�p�����[�^�̎w�肳�ꂽ�^�ł���܂���");

    auto p = param[path].GetString();
    auto temp = super::_resource_manager.lock()->Get<std::shared_ptr<Mof::CMeshContainer>>(p);
    this->SetMeshContainer(temp);

    const char* color = "color";
    if (param.HasMember(color)) {
        _ASSERT_EXPR(param[color].IsArray(), L"�p�����[�^�̎w�肳�ꂽ�^�ł���܂���");
        for (int i = 0, n = param[color].GetArray().Size(); i < n; i++) {
            _color.fv[i] = param[color].GetArray()[i].GetFloat();
        } // for
    } // if
    else {
        _color = math::vec4::kOne;
    } // else
}

void my::MeshComponent::SetMeshContainer(const std::shared_ptr<Mof::CMeshContainer>& ptr) {
    this->_mesh = ptr;
}

std::string my::MeshComponent::GetType(void) const {
    return "MeshComponent";
}

std::shared_ptr<Mof::CMeshContainer> my::MeshComponent::GetMeshContainer(void) const {
    return this->_mesh.lock();
}

Mof::CVector4 my::MeshComponent::GetColor(void) const {
    return this->_color;
}

bool my::MeshComponent::Render(void) {
    if (!super::GetOwner()->InCameraRange()) {
        return false;
    } // if

    auto owner = super::GetOwner();
    // �`��
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

bool my::MeshComponent::Release(void) {
    super::Release();
    _mesh.reset();
    return true;
}

std::shared_ptr<my::Component> my::MeshComponent::Clone(void) {
    return std::make_shared<my::MeshComponent>(*this);
}