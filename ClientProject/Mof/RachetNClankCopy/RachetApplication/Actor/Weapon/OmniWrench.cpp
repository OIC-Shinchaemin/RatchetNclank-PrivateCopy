#include "OmniWrench.h"


my::OmniWrench::OmniWrench() :
    super() {
    super::SetTag("OmniWrench");
}

my::OmniWrench ::~OmniWrench() {
}

bool my::OmniWrench::Initialize(my::Actor::Param* param) {
    super::Initialize(param);

    super::SetScale(Mof::CVector3());
    return true;
}
