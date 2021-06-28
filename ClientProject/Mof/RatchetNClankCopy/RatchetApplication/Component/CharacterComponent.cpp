#include "CharacterComponent.h"


ratchet::component::CharacterComponent::CharacterComponent(int priority) :
    super(priority),
    _volume(0.0f),
    _height(0.0f) {
}

ratchet::component::CharacterComponent::CharacterComponent(const CharacterComponent& obj) :
    super(obj),
    _volume(obj._volume),
    _height(obj._height) {
}

ratchet::component::CharacterComponent::~CharacterComponent() {
}

void ratchet::component::CharacterComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
    const char* height = "height";
    _ASSERT_EXPR(param.HasMember(height), L"指定のパラメータがありません");
    _ASSERT_EXPR(param[height].IsFloat(), L"パラメータの指定された型でありません");
    _height = param[height].GetFloat();

    const char* volume = "volume";
    _ASSERT_EXPR(param.HasMember(volume), L"指定のパラメータがありません");
    _ASSERT_EXPR(param[volume].IsFloat(), L"パラメータの指定された型でありません");
    _volume = param[volume].GetFloat();
}

std::string ratchet::component::CharacterComponent::GetType(void) const {
    return "CharacterComponent";
}

float ratchet::component::CharacterComponent::GetVolume(void) const {
    return this->_volume;
}

float ratchet::component::CharacterComponent::GetHeight(void) const {
    return this->_height;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::CharacterComponent::Clone(void) {
    return std::make_shared<ratchet::component::CharacterComponent>(*this);
}