#include "Ship.h"

#include "../../Factory/Builder/IBuilder.h"


ratchet::actor::vehicle::Ship::Ship() :
    super() {
}

ratchet::actor::vehicle::Ship::~Ship() {
}

void ratchet::actor::vehicle::Ship::Construct(const std::shared_ptr<ratchet::factory::builder::IBuilder>& builder) {
    super::Construct(builder);
}