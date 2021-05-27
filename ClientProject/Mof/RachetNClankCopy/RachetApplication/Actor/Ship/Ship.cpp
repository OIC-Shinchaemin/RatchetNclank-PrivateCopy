#include "Ship.h"


my::Ship::Ship() :
    super() {
}

my::Ship::~Ship() {
}

void my::Ship::Construct(const std::shared_ptr<class IBuilder>& builder) {
    super::Construct(builder);
}