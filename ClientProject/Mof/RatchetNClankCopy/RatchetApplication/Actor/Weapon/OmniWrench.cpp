#include "OmniWrench.h"


ratchet::actor::weapon::OmniWrench::OmniWrench() :
    super() {
    super::SetTag("OmniWrench");
}

ratchet::actor::weapon::OmniWrench ::~OmniWrench() {
}

bool ratchet::actor::weapon::OmniWrench::Initialize(ratchet::actor::Actor::Param* param) {
    super::Initialize(param);

    super::SetScale(Mof::CVector3());
    return true;
}
