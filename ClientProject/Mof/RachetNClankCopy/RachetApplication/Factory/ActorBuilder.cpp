#include "ActorBuilder.h"

my::ActorBuilder::ActorBuilder() :
    _components() {
}

my::ActorBuilder::~ActorBuilder() {
}

void my::ActorBuilder::Construct(std::any shared_this) {
    auto ptr = std::any_cast<std::shared_ptr<my::Actor>>(shared_this);
    for (auto com : _components) {
        ptr->AddComponent(com);
    } // for
}