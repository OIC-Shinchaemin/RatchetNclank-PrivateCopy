#include "Shop.h"


rachet::Shop::Shop() :
    super() {
}

rachet::Shop::~Shop() {
}

bool rachet::Shop::Update(float delta_time) {
    super::Update(delta_time);
    return true;
}

bool rachet::Shop::Release(void) {
    super::Release();
    return true;
}