#include "OmniWrenchBuilder.h"


ratchet::factory::builder::actor::OmniWrenchBuilder::OmniWrenchBuilder() :
    super() {
}

ratchet::factory::builder::actor::OmniWrenchBuilder::~OmniWrenchBuilder() {
}

void ratchet::factory::builder::actor::OmniWrenchBuilder::Release(void) {
    super::Release();
    //_resource.reset();
}

void ratchet::factory::builder::actor::OmniWrenchBuilder::Construct(std::any shared_this) {
    super::Construct(shared_this);
    auto temp = std::any_cast<std::shared_ptr<ratchet::Actor>>(shared_this);
}