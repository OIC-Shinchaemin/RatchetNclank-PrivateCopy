#include "Ship.h"


ratchet::Ship::Ship() :
    super() {
}

ratchet::Ship::~Ship() {
}

void ratchet::Ship::Construct(const std::shared_ptr<class IBuilder>& builder) {
    super::Construct(builder);
}