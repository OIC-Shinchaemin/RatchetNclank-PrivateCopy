#include "GameWorld.h"


ratchet::game::GameWorld::GameWorld() :
    _actors() {
    _actors.reserve(64);
}

ratchet::game::GameWorld::~GameWorld() {
}

ratchet::game::GameWorld::ActorPtr ratchet::game::GameWorld::GetActor(uint32_t index) const {
    if (_actors.size() <= index) {
        return nullptr;
    } // if
    return _actors.at(index);
}

void ratchet::game::GameWorld::AddActor(const ActorPtr& actor) {
    _actors.emplace_back(actor);
}

void ratchet::game::GameWorld::RemoveActor(const ActorPtr& actor) {
    ut::SwapPopback(_actors, actor);
}

bool ratchet::game::GameWorld::Input(void) {
    // input
    for (auto& actor : _actors) {
        auto state = actor->GetState();
        if (state == ratchet::ActorState::Active) {
            actor->Input();
        } // if
    } // for
    return true;
}

bool ratchet::game::GameWorld::Update(float delta_time) {
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

void ratchet::game::GameWorld::UpdateDebug(void) {
}

void ratchet::game::GameWorld::Reset(void) {
    _actors.clear();
}