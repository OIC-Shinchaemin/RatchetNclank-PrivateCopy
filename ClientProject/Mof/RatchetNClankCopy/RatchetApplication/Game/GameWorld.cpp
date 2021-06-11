#include "GameWorld.h"


ratchet::GameWorld::GameWorld() :
    _actors() {
    _actors.reserve(64);
}

ratchet::GameWorld::~GameWorld() {
}

ratchet::GameWorld::ActorPtr ratchet::GameWorld::GetActor(uint32_t index) const {
    if (_actors.size() <= index) {
        return nullptr;
    } // if
    return _actors.at(index);
}

void ratchet::GameWorld::AddActor(const ActorPtr& actor) {
    _actors.emplace_back(actor);
}

void ratchet::GameWorld::RemoveActor(const ActorPtr& actor) {
    ut::SwapPopback(_actors, actor);
}

bool ratchet::GameWorld::Input(void) {
    // input
    for (auto& actor : _actors) {
        auto state = actor->GetState();
        if (state == ratchet::ActorState::Active) {
            actor->Input();
        } // if
    } // for
    return true;
}

bool ratchet::GameWorld::Update(float delta_time) {
    // update
    for (auto& actor : _actors) {
        auto state = actor->GetState();
        if (state == ratchet::ActorState::Active ||
            state == ratchet::ActorState::Sleep ||
            state == ratchet::ActorState::Hide) {
            actor->Update(delta_time);
        } // if
    } // for
    return true;
}

void ratchet::GameWorld::UpdateDebug(void) {
}

void ratchet::GameWorld::Reset(void) {
    _actors.clear();
}