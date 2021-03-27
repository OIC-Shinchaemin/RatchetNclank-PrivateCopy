#include "Pyrocitor.h"

my::Pyrocitor::Pyrocitor() :
    super() {
    super::SetPosition(Mof::CVector3(0.0f, 0.0f, 0.0f));
    float s = 0.2f;
    super::SetScale(Mof::CVector3(s, s, s));
    super::_mesh = my::ResourceLocator::GetResource<Mof::CMeshContainer>("../Resource/mesh/pyrocitor/scene.mom");
}

my::Pyrocitor::~Pyrocitor() {
}