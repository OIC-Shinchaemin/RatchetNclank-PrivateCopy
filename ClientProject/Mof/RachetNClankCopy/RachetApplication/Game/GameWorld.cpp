#include "GameWorld.h"


rachet::GameWorld::GameWorld() :
    _actors() {
    _actors.reserve(64);
}

rachet::GameWorld::~GameWorld() {
}

rachet::GameWorld::ActorPtr rachet::GameWorld::GetActor(uint32_t index) const {
    if (_actors.size() <= index) {
        return nullptr;
    } // if
    return _actors.at(index);
}

void rachet::GameWorld::AddActor(const ActorPtr& actor) {
    _actors.emplace_back(actor);
}

void rachet::GameWorld::RemoveActor(const ActorPtr& actor) {
    ut::SwapPopback(_actors, actor);
}

bool rachet::GameWorld::Input(void) {
    // input
    for (auto& actor : _actors) {
        auto state = actor->GetState();
        if (state == rachet::ActorState::Active) {
            actor->Input();
        } // if
    } // for
    return true;
}

bool rachet::GameWorld::Update(float delta_time) {
    // update
    for (auto& actor : _actors) {
        auto state = actor->GetState();
        if (state == rachet::ActorState::Active ||
            state == rachet::ActorState::Sleep ||
            state == rachet::ActorState::Hide) {
            actor->Update(delta_time);
        } // if
    } // for
    return true;
}

void rachet::GameWorld::UpdateDebug(void) {
}

void rachet::GameWorld::Reset(void) {
    _actors.clear();
}