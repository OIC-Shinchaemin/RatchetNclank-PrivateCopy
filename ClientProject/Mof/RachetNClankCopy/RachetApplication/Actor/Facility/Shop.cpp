#include "Shop.h"


my::Shop::Shop() :
    super() {
}

my::Shop::~Shop() {
}

bool my::Shop::Update(float delta_time) {
    super::Update(delta_time);
    return true;
}

bool my::Shop::Release(void) {
    super::Release();
    return true;
}