#include "PhysicsWorld.h"

#include "My/Core/Utility.h"
#include "../Component/Collision/Algolithm/PlayerCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/EnemyCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/EnemySightCollisionAlgolithm.h"


std::shared_ptr<my::CollisionAlgolithm> my::PhysicsWorld::CreateAlgolithm(const char* type) {
    std::shared_ptr<my::CollisionAlgolithm> ptr = nullptr;
    if (type == "PlayerEnemyCollisionAlgolithm") {
        ptr = std::make_shared<my::PlayerEnemyCollisionAlgolithm>();
    } // if
    if (type == "EnemyPlayerCollisionAlgolithm") {
        ptr = std::make_shared<my::EnemyPlayerCollisionAlgolithm>();
    } // if
    if (type == "EnemySightPlayerCollisionAlgolithm") {
        ptr = std::make_shared<my::EnemySightPlayerCollisionAlgolithm>();
    } // if
    return ptr;
}

my::PhysicsWorld::PhysicsWorld() :
    _objects() {
    const char* types[] = {
        "PlayerEnemyCollisionAlgolithm",
        "EnemyPlayerCollisionAlgolithm",
        "EnemySightPlayerCollisionAlgolithm",
    };
    for (auto type : types) {
        auto temp = CollisionPair();
        temp.algo = this->CreateAlgolithm(type);
        _objects.push_back(temp);
    } // for
}

my::PhysicsWorld::~PhysicsWorld() {
    _objects.clear();
}

void my::PhysicsWorld::AddActor(const ActorPtr& actor) {
    auto& work = actor->GetCollisionObjects();
    for (auto& ptr : work) {
        auto type = ptr->GetType();
        for (auto& obj : _objects) {
            if (type == obj.algo->GetLayerType()) {
                obj.layers.push_back(ptr);
            } // if
            if (type == obj.algo->GetTargetType()) {
                obj.targets.push_back(ptr);
            } // if
        } // for
    } // for
}

void my::PhysicsWorld::RemoveActor(const ActorPtr& actor) {
    auto& work = actor->GetCollisionObjects();
    for (auto& ptr : work) {
        for (auto& obj : _objects) {
            ut::EraseRemove(obj.layers, ptr);
            ut::EraseRemove(obj.targets, ptr);
        } // for
    } // for
}

bool my::PhysicsWorld::Update(void) {
    for (auto& obj : _objects) {
        for (auto& layer : obj.layers) {
            for (auto& target : obj.targets) {
                if (layer == target) {
                    continue;
                } // if
                auto info = my::CollisionInfo();
                if (!obj.algo->IsCollision(layer, target, info)) {
                    // Õ“ËI—¹
                    if (layer->ExistCollisionedObject(target)) {
                        layer->ExecuteExitFunction(target->GetType(), info);
                        layer->RemoveCollisionedObject(target);
                    } // if
                    continue;
                } // if
                // Õ“ËŠJŽn
                if (!layer->ExistCollisionedObject(target)) {
                    layer->ExecuteEnterFunction(target->GetType(), info);
                    layer->AddCollisionedObject(target);
                } // if
                // Õ“Ë’†
                else {
                    layer->ExecuteStayFunction(target->GetType(), info);
                } // else
            } // for
        } // for
    } // for
    return true;
}