#include "Shop.h"


ratchet::Shop::Shop() :
    super() {
}

ratchet::Shop::~Shop() {
}

bool ratchet::Shop::Update(float delta_time) {
    super::Update(delta_time);
    return true;
}

bool ratchet::Shop::Release(void) {
    super::Release();
    return true;
}