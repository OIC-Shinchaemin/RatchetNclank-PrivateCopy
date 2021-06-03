#include "GameWorld.h"


my::GameWorld::GameWorld() :
    _actors() {
    _actors.reserve(64);
}

my::GameWorld::~GameWorld() {
}

my::GameWorld::ActorPtr my::GameWorld::GetActor(uint32_t index) const {
    if (_actors.size() <= index) {
        return nullptr;
    } // if
    return _actors.at(index);
}

void my::GameWorld::AddActor(const ActorPtr& actor) {
    _actors.emplace_back(actor);
}

void my::GameWorld::RemoveActor(const ActorPtr& actor) {
    ut::SwapPopback(_actors, actor);
}

bool my::GameWorld::Input(void) {
    // input
    for (auto& actor : _actors) {
        auto state = actor->GetState();
        if (state == my::ActorState::Active) {
            actor->Input();
        } // if
    } // for
    return true;
}

bool my::GameWorld::Update(float delta_time) {
    // update
    for (auto& actor : _actors) {
        auto state = actor->GetState();
        if (state == my::ActorState::Active ||
            state == my::ActorState::Sleep ||
            state == my::ActorState::Hide) {
            actor->Update(delta_time);
        } // if
    } // for
    return true;
}

void my::GameWorld::UpdateDebug(void) {
}

void my::GameWorld::Reset(void) {
    _actors.clear();
}