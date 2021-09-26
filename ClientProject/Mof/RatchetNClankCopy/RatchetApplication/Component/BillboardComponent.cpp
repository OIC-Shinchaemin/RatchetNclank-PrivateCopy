#include "BillboardComponent.h"


ratchet::component::BillboardComponent::BillboardComponent(int priority) :
    super(priority),
    _texture(),
    _color(),
    _offset_position(),
    _offset_rotation() {
}

ratchet::component::BillboardComponent::BillboardComponent(const ratchet::component::BillboardComponent& obj) :
    super(obj),
    _texture(obj._texture),
    _color(obj._color),
    _offset_position(),
    _offset_rotation() {
}

ratchet::component::BillboardComponent::~BillboardComponent() {
}

void ratchet::component::BillboardComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
    const char* path = "path";

    _ASSERT_EXPR(param.HasMember(path), L"指定のパラメータがありません");
    _ASSERT_EXPR(param[path].IsString(), L"パラメータの指定された型でありません");

    auto p = param[path].GetString();
    auto temp = super::_resource_manager.lock()->Get<std::shared_ptr<Mof::CTexture>>(p);
    this->SetTexture(temp);

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

void ratchet::component::BillboardComponent::SetTexture(const std::shared_ptr<Mof::CTexture>& ptr) {
    this->_texture = ptr;
}

void ratchet::component::BillboardComponent::SetOffsetPosition(const Mof::CVector3& value) {
    this->_offset_position = value;
}

void ratchet::component::BillboardComponent::SetOffsetRotation(const Mof::CVector3& value) {
    this->_offset_rotation = value;
}

std::string ratchet::component::BillboardComponent::GetType(void) const {
    return "BillboardComponent";
}

std::shared_ptr<Mof::CTexture> ratchet::component::BillboardComponent::GetTexture(void) const {
    return this->_texture.lock();
}

Mof::CVector4 ratchet::component::BillboardComponent::GetColor(void) const {
    return this->_color;
}

bool ratchet::component::BillboardComponent::Render(void) {
    if (!super::GetOwner()->InCameraRange()) {
        return false;
    } // if

    auto owner = super::GetOwner();
    // 描画
    if (auto tex = this->GetTexture(); tex) {
        Mof::CMatrix44 scale, rotate, translate;
        Mof::CQuaternion quat; quat.Rotation(this->_offset_rotation + owner->GetRotate());
        
        scale.Scaling(owner->GetScale(), scale);
        quat.ConvertMatrixTranspose(rotate);
        translate.Translation(this->_offset_position + owner->GetPosition(), translate);

        Mof::CMatrix44 world = scale * rotate * translate;
        auto camera = ::CGraphicsUtilities::GetCamera();
        tex->Render(camera->GetBillBoardMatrix() * world);

        //CGraphicsUtilities::RenderTexture();
        //tex->Render(world, _rectangle.value());
    } // if
    return true;
}

bool ratchet::component::BillboardComponent::Release(void) {
    super::Release();
    _texture.reset();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::BillboardComponent::Clone(void) {
    return std::make_shared<ratchet::component::BillboardComponent>(*this);
}