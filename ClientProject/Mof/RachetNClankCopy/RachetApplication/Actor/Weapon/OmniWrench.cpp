#include "OmniWrench.h"


ratchet::OmniWrench::OmniWrench() :
    super() {
    super::SetTag("OmniWrench");
}

ratchet::OmniWrench ::~OmniWrench() {
}

bool ratchet::OmniWrench::Initialize(ratchet::Actor::Param* param) {
    super::Initialize(param);

    super::SetScale(Mof::CVector3());
    return true;
}
