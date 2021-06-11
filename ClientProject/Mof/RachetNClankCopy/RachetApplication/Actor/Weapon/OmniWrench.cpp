#include "OmniWrench.h"


rachet::OmniWrench::OmniWrench() :
    super() {
    super::SetTag("OmniWrench");
}

rachet::OmniWrench ::~OmniWrench() {
}

bool rachet::OmniWrench::Initialize(rachet::Actor::Param* param) {
    super::Initialize(param);

    super::SetScale(Mof::CVector3());
    return true;
}
