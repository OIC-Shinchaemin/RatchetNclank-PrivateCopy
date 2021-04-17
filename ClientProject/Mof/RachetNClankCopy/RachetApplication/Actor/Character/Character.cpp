#include "Character.h"


my::Character::Character() :
    super()
//    ,
//    _volume(0.5f),
//    _height(1.0f) 
{
}

my::Character::~Character() {
}
/*
float my::Character::GetVolume(void) const {
    return this->_volume;
}

float my::Character::GetHeight(void) const {
    return this->_height;
}

Mof::CSphere my::Character::GetSphere(void) const {
    auto pos = super::GetPosition();
    pos.y += _height;
    return Mof::CSphere(pos, _volume);
}
*/

void my::Character::RenderDebug(void) {
    //::CGraphicsUtilities::RenderLineSphere(this->GetSphere(), def::color_rgba::kRed);
}