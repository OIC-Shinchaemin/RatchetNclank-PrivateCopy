#include "BombGlove.h"


my::BombGlove::BombGlove() :
    super() {
    super::SetPosition(Mof::CVector3(0.0f, 0.0f, 0.0f));
    float s = 0.7f;
    super::SetScale(Mof::CVector3(s, s, s));
    super::_mesh = my::ResourceLocator::GetResource<Mof::CMeshContainer>("../Resource/mesh/bomb_glove/scene.mom");
}

my::BombGlove::~BombGlove() {
}