#include "GameWorld.h"


my::GameWorld::GameWorld() :
    _actors() {
    _actors.reserve(30);
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
    // update
    for (auto& actor : _actors) {
        actor->Input();
    } // for
    return true;
}

bool my::GameWorld::Update(float delta_time) {
    // update
    for (auto& actor : _actors) {
        actor->Update(delta_time);
    } // for
    return true;
}

void my::GameWorld::UpdateDebug(void) {
}

void my::GameWorld::Reset(void) {
    _actors.clear();
}