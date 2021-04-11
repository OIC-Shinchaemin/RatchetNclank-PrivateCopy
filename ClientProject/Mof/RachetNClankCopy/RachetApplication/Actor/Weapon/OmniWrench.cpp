#include "OmniWrench.h"


my::OmniWrench::OmniWrench() :
    super() {
    super::SetPosition(Mof::CVector3(0.0f, 2.0f, 0.0f));
    super::SetScale(Mof::CVector3(1.0f, 1.0f, 1.0f));
    //super::_mesh = my::ResourceLocator::GetResource<Mof::CMeshContainer>("../Resource/mesh/omni_wrench/scene.mom");
}

my::OmniWrench ::~OmniWrench() {
}
