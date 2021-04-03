#include "PhysicWorld.h"

#include "My/Core/Utility.h"
#include "../Collision/PlayerCollisionAlgolithm.h"
#include "../Collision/EnemyCollisionAlgolithm.h"


std::shared_ptr<my::CollisionAlgolithm> my::PhysicWorld::CreateAlgolithm(const char* type) {
    std::shared_ptr<my::CollisionAlgolithm> ptr = nullptr;
    if (type == "PlayerEnemyCollisionAlgolithm") {
        ptr = std::make_shared<my::PlayerEnemyCollisionAlgolithm>();
    } // if
    if (type == "EnemyPlayerCollisionAlgolithm") {
        ptr = std::make_shared<my::EnemyPlayerCollisionAlgolithm>();
    } // if
    return ptr;
}

my::PhysicWorld::PhysicWorld() :
    _objects() {
    const char* types[] = {
        "PlayerEnemyCollisionAlgolithm",
        "EnemyPlayerCollisionAlgolithm",
    };
    for (auto type : types) {
        auto temp = CollisionPair();
        temp.algo = this->CreateAlgolithm(type);
        _objects.push_back(temp);
    } // for
}

my::PhysicWorld::~PhysicWorld() {
    _objects.clear();
}

void my::PhysicWorld::AddActor(const ActorPtr& actor) {
    auto ptr = actor->GetCollisionObject();
    auto type = ptr->GetType();
    for (auto& obj : _objects) {
        if (type == obj.algo->GetLayerType()) {
            obj.layers.push_back(ptr);
        } // if
        if (type == obj.algo->GetTargetType()) {
            obj.targets.push_back(ptr);
        } // if
    } // for
}

void my::PhysicWorld::RemoveActor(const ActorPtr& actor) {
    auto ptr = actor->GetCollisionObject();
    for (auto& obj : _objects) {
        ut::EraseRemove(obj.layers, ptr);
        ut::EraseRemove(obj.targets, ptr);
    } // for
}

bool my::PhysicWorld::Update(void) {
    for (auto& obj : _objects) {
        for (auto& lay : obj.layers) {
            for (auto& target : obj.targets) {
                if (lay == target) {
                    continue;
                } // if
                auto info = my::CollisionInfo();
                if (!obj.algo->IsCollision(lay, target, info)) {
                    continue;
                } // if
                obj.algo->Collision(lay, target, info);
            } // for
        } // for
    } // for
    return true;
}