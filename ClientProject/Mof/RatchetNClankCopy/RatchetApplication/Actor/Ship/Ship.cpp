#include "Ship.h"

#include "../../Factory/Builder/IBuilder.h"


ratchet::Ship::Ship() :
    super() {
}

ratchet::Ship::~Ship() {
}

void ratchet::Ship::Construct(const std::shared_ptr<ratchet::factory::builder::IBuilder>& builder) {
    super::Construct(builder);
}