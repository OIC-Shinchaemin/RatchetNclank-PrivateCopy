#include "PhysicsWorld.h"

#include "My/Core/Utility.h"
#include "../Component/Collision/Algolithm/PlayerEnemyCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/PlayerEnemyAttackCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/EnemyPlayerCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/SightPlayerCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/SightEnemyCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/EnemyAttackPlayerCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/EnemyBlasterBulletCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/EnemyBombGloveBulletCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/BlasterBulletEnemyCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/BombGloveBulletEnemyCollisionAlgolithm.h"


my::PhysicsWorld::PhysicsWorld() :
    _layers() {
    collision_algolithm_factory.Register<my::PlayerEnemyCollisionAlgolithm>("PlayerEnemyCollisionAlgolithm");
    collision_algolithm_factory.Register<my::PlayerEnemyAttackCollisionAlgolithm>("PlayerEnemyAttackCollisionAlgolithm");
    collision_algolithm_factory.Register<my::EnemyPlayerCollisionAlgolithm>("EnemyPlayerCollisionAlgolithm");
    collision_algolithm_factory.Register<my::SightPlayerCollisionAlgolithm>("SightPlayerCollisionAlgolithm");
    collision_algolithm_factory.Register<my::SightEnemyCollisionAlgolithm>("SightEnemyCollisionAlgolithm");
    collision_algolithm_factory.Register<my::EnemyAttackPlayerCollisionAlgolithm>("EnemyAttackPlayerCollisionAlgolithm");
    collision_algolithm_factory.Register<my::EnemyBlasterBulletCollisionAlgolithm>("EnemyBlasterBulletCollisionAlgolithm");
    collision_algolithm_factory.Register<my::EnemyBombGloveBulletCollisionAlgolithm>("EnemyBombGloveBulletCollisionAlgolithm");
    collision_algolithm_factory.Register<my::BlasterBulletEnemyCollisionAlgolithm>("BlasterBulletEnemyCollisionAlgolithm");
    collision_algolithm_factory.Register<my::BombGloveBulletEnemyCollisionAlgolithm>("BombGloveBulletEnemyCollisionAlgolithm");

    const char* types[] = {
        "PlayerEnemyCollisionAlgolithm",
        "PlayerEnemyAttackCollisionAlgolithm",
        "EnemyPlayerCollisionAlgolithm",
        "SightPlayerCollisionAlgolithm",
        "SightEnemyCollisionAlgolithm",
        "EnemyAttackPlayerCollisionAlgolithm",
        "EnemyBlasterBulletCollisionAlgolithm",
        "EnemyBombGloveBulletCollisionAlgolithm",
        "BlasterBulletEnemyCollisionAlgolithm",
        "BombGloveBulletEnemyCollisionAlgolithm",
    };
    for (auto type : types) {
        auto temp = CollisionLayer();
        temp.algo = collision_algolithm_factory.Create(type);
        _layers.push_back(temp);
    } // for
}

my::PhysicsWorld::~PhysicsWorld() {
    _layers.clear();
}

void my::PhysicsWorld::AddActor(const ActorPtr& actor) {
    std::vector<std::weak_ptr<my::CollisionComponent>> work;
    actor->GetComponents<my::CollisionComponent>(work);
    
    for (auto& ptr : work) {
        auto type = ptr.lock()->GetType();
        for (auto& layer: _layers) {
            if (type == layer.algo->GetLayerType()) {
                layer.objects.push_back(ptr.lock());
            } // if
            if (type == layer.algo->GetTargetType()) {
                layer.targets.push_back(ptr.lock());
            } // if
        } // for
    } // for
}

void my::PhysicsWorld::RemoveActor(const ActorPtr& actor) {
    std::vector<std::weak_ptr<my::CollisionComponent>> work;
    actor->GetComponents<my::CollisionComponent>(work);

    for (auto& ptr : work) {
        for (auto& layer : _layers) {
            ut::EraseRemove(layer.objects, ptr.lock());
            ut::EraseRemove(layer.targets, ptr.lock());
        } // for
    } // for
}

bool my::PhysicsWorld::Update(void) {
    for (auto& layer : _layers) {
        for (auto& object : layer.objects) {
            for (auto& target : layer.targets) {
                if (object == target) {
                    continue;
                } // if
                auto info = my::CollisionInfo();
                if (!layer.algo->IsCollision(object, target, info)) {
                    // Õ“ËI—¹
                    if (object->ExistCollisionedObject(target)) {
                        object->ExecuteExitFunction(target->GetType(), info);
                        object->RemoveCollisionedObject(target);
                    } // if
                    continue;
                } // if
                // Õ“ËŠJŽn
                if (!object->ExistCollisionedObject(target)) {
                    object->ExecuteEnterFunction(target->GetType(), info);
                    object->AddCollisionedObject(target);
                } // if
                // Õ“Ë’†
                else {
                    object->ExecuteStayFunction(target->GetType(), info);
                } // else
            } // for
        } // for
    } // for
    return true;
}

void my::PhysicsWorld::CollisionStage(Stage* stage) {
    Mof::LPMeshContainer mesh = &*stage->GetStaticStageMesh();
    for (auto& layer : _layers) {
        for (auto& object : layer.objects) {
            object->CollisionStage(mesh);
        } // for
    } // for
}