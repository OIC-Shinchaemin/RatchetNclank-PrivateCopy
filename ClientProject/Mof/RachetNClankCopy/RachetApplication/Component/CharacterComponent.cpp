#include "CharacterComponent.h"


my::CharacterComponent::CharacterComponent(int priority) :
    super(priority),
    _volume(0.5f),
    _height(1.0f) {
}

my::CharacterComponent::CharacterComponent(const CharacterComponent& obj) :
    super(obj),
    _volume(obj._volume),
    _height(obj._height) {
}

my::CharacterComponent::~CharacterComponent() {
}

std::string my::CharacterComponent::GetType(void) const {
    return "CharacterComponent";
}

float my::CharacterComponent::GetVolume(void) const {
    return this->_volume;
}

float my::CharacterComponent::GetHeight(void) const {
    return this->_height;
}

std::shared_ptr<my::Component> my::CharacterComponent::Clone(void) {
    return std::make_shared<my::CharacterComponent>(*this);
}