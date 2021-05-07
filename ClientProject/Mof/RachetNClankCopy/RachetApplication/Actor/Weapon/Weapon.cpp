#include "Weapon.h"

#include "../Bullet/Bullet.h"


my::Weapon::Weapon() :
    super(),
    _mesh(){
}

my::Weapon::~Weapon() {
}

bool my::Weapon::Update(float delta_time) {
    super::Update(delta_time);
    return true;
}