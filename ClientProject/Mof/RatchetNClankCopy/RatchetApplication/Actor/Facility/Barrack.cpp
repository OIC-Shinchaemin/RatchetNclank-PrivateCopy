#include "Barrack.h"


ratchet::actor::facility::Barrack::Barrack() :
    super() {
}

ratchet::actor::facility::Barrack ::~Barrack() {
}

bool ratchet::actor::facility::Barrack::Update(float delta_time) {
    super::Update(delta_time);
    return true;
}

bool ratchet::actor::facility::Barrack::Release(void) {
    super::Release();
    return true;
}