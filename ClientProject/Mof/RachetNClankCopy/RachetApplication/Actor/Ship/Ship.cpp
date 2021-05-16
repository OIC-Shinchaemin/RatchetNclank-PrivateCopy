#include "Ship.h"

#include "../../Component/Ship/ShipComponent.h"


my::Ship::Ship() :
    super(),
    _enable(false) {
}

my::Ship::~Ship() {
}

void my::Ship::OnNotify(const char* type, const std::shared_ptr<my::Actor>& ptr) {
    if (type == "ShipCollision") {
        if (_enable) {
            super::GetComponent<my::ShipComponent>()->Activate();
        } // if
    } // if
    else if (type == "GimmickAction") {
        _enable = true;
    } // else if
}

bool my::Ship::IsEnable(void) const {
    return this->_enable;
}

void my::Ship::Construct(const std::shared_ptr<class IBuilder>& builder) {
    super::Construct(builder);
}