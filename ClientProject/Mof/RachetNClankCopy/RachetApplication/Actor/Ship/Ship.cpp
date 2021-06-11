#include "Ship.h"


rachet::Ship::Ship() :
    super() {
}

rachet::Ship::~Ship() {
}

void rachet::Ship::Construct(const std::shared_ptr<class IBuilder>& builder) {
    super::Construct(builder);
}