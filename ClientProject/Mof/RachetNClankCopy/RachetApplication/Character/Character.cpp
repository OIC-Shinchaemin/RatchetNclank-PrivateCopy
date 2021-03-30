#include "Character.h"


my::Character::Character() :
    super(),
    _mesh(),
    _volume(1.0f),
    _height(1.0f){
}

my::Character::~Character() {
}

Mof::CSphere my::Character::GetSphere(void) const {
    return Mof::CSphere(super::GetPosition(), _volume);
}

bool my::Character::Initialize(const def::Transform& transform) {
    super::Initialize(transform);
    return true;
}


bool my::Character::Release(void) {
    super::Release();
    return true;
}

void my::Character::DebugRender(void) {
    ::CGraphicsUtilities::RenderLineSphere(this->GetSphere(), def::color_rgba::kRed);
}