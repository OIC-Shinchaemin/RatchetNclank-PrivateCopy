#include "PhysicsWorld.h"

#include "My/Core/Utility.h"
#include "../Component/Collision/Algolithm/PlayerEnemyCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/PlayerEnemyAttackCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/EnemyPlayerCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/EnemySightPlayerCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/EnemyAttackPlayerCollisionAlgolithm.h"


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
    if (type == "EnemyAttackPlayerCollisionAlgolithm") {
        ptr = std::make_shared<my::EnemyAttackPlayerCollisionAlgolithm>();
    } // if
    return ptr;
}

my::PhysicsWorld::PhysicsWorld() :
    _objects() {
    collision_algolithm_factory.Register<my::PlayerEnemyCollisionAlgolithm>("PlayerEnemyCollisionAlgolithm");
    collision_algolithm_factory.Register<my::PlayerEnemyAttackCollisionAlgolithm>("PlayerEnemyAttackCollisionAlgolithm");
    collision_algolithm_factory.Register<my::EnemyPlayerCollisionAlgolithm>("EnemyPlayerCollisionAlgolithm");
    collision_algolithm_factory.Register<my::EnemySightPlayerCollisionAlgolithm>("EnemySightPlayerCollisionAlgolithm");
    collision_algolithm_factory.Register<my::EnemyAttackPlayerCollisionAlgolithm>("EnemyAttackPlayerCollisionAlgolithm");

    const char* types[] = {
        "PlayerEnemyCollisionAlgolithm",
        "PlayerEnemyAttackCollisionAlgolithm",
        "EnemyPlayerCollisionAlgolithm",
        "EnemySightPlayerCollisionAlgolithm",
        "EnemyAttackPlayerCollisionAlgolithm",
    };
    for (auto type : types) {
        auto temp = CollisionPair();
        temp.algo = collision_algolithm_factory.Create(type);
        _objects.push_back(temp);
    } // for
}

my::PhysicsWorld::~PhysicsWorld() {
    _objects.clear();
}

void my::PhysicsWorld::AddActor(const ActorPtr& actor) {
    std::vector<std::weak_ptr<my::CollisionObject>> work;
    actor->GetComponents<my::CollisionObject>(work);
    
    for (auto& ptr : work) {
        auto type = ptr.lock()->GetType();
        for (auto& obj : _objects) {
            if (type == obj.algo->GetLayerType()) {
                obj.layers.push_back(ptr.lock());
            } // if
            if (type == obj.algo->GetTargetType()) {
                obj.targets.push_back(ptr.lock());
            } // if
        } // for
    } // for
}

void my::PhysicsWorld::RemoveActor(const ActorPtr& actor) {
    std::vector<std::weak_ptr<my::CollisionObject>> work;
    actor->GetComponents<my::CollisionObject>(work);

    for (auto& ptr : work) {
        for (auto& obj : _objects) {
            ut::EraseRemove(obj.layers, ptr.lock());
            ut::EraseRemove(obj.targets, ptr.lock());
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