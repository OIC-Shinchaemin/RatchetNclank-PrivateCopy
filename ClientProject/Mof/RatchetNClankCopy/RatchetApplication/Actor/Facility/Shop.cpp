#include "Shop.h"


ratchet::actor::facility::Shop::Shop() :
    super() {
}

ratchet::actor::facility::Shop::~Shop() {
}

bool ratchet::actor::facility::Shop::Update(float delta_time) {
    super::Update(delta_time);
    return true;
}

bool ratchet::actor::facility::Shop::Release(void) {
    super::Release();
    return true;
}