#include "PhysicsWorld.h"

#include "My/Core/Utility.h"
#include "../Component/Collision/Algolithm/CollisionAlgolithmDefine.h"
#include "../Component/Collision/Algolithm/PlayerEnemyCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/PlayerEnemyAttackCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/PlayerShipCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/EnemyPlayerCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/SightPlayerCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/SightEnemyCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/EnemyAttackPlayerCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/EnemyBombGloveBulletCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/EnemyPyrocitorBulletCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/EnemyBlasterBulletCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/EnemyBombGloveEffectCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/BlasterBulletEnemyCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/BombGloveBulletEnemyCollisionAlgolithm.h"


void my::PhysicsWorld::GenerateLayer(void) {
    
    const char* types[] = {
      my::CollisionAlgolithmType::kPlayerEnemyCollisionAlgolithm.c_str(),
      my::CollisionAlgolithmType::kPlayerEnemyAttackCollisionAlgolithm.c_str(),
      my::CollisionAlgolithmType::kPlayerShipCollisionAlgolithm.c_str(),
      my::CollisionAlgolithmType::kEnemyPlayerCollisionAlgolithm.c_str(),
      my::CollisionAlgolithmType::kSightPlayerCollisionAlgolithm.c_str(),
      my::CollisionAlgolithmType::kSightEnemyCollisionAlgolithm.c_str(),
      my::CollisionAlgolithmType::kEnemyAttackPlayerCollisionAlgolithm.c_str(),
      my::CollisionAlgolithmType::kEnemyBombGloveBulletCollisionAlgolithm.c_str(),
      my::CollisionAlgolithmType::kEnemyPyrocitorBulletCollisionAlgolithm.c_str(),
      my::CollisionAlgolithmType::kEnemyBlasterBulletCollisionAlgolithm.c_str(),
      my::CollisionAlgolithmType::kEnemyBombGloveEffectCollisionAlgolithm.c_str(),
      my::CollisionAlgolithmType::kBlasterBulletEnemyCollisionAlgolithm.c_str(),
      my::CollisionAlgolithmType::kBombGloveBulletEnemyCollisionAlgolithm.c_str(),
    };
    for (auto type : types) {
        auto temp = CollisionLayer();
        temp.algo = collision_algolithm_factory.Create(type);
        _layers.push_back(temp);
    } // for
}

my::PhysicsWorld::PhysicsWorld() :
    _layers() {
    collision_algolithm_factory.Register<my::PlayerEnemyCollisionAlgolithm>(my::CollisionAlgolithmType::kPlayerEnemyCollisionAlgolithm);
    collision_algolithm_factory.Register<my::PlayerEnemyAttackCollisionAlgolithm>(my::CollisionAlgolithmType::kPlayerEnemyAttackCollisionAlgolithm);
    collision_algolithm_factory.Register<my::PlayerShipCollisionAlgolithm>(my::CollisionAlgolithmType::kPlayerShipCollisionAlgolithm);
    collision_algolithm_factory.Register<my::EnemyPlayerCollisionAlgolithm>(my::CollisionAlgolithmType::kEnemyPlayerCollisionAlgolithm);
    collision_algolithm_factory.Register<my::SightPlayerCollisionAlgolithm>(my::CollisionAlgolithmType::kSightPlayerCollisionAlgolithm);
    collision_algolithm_factory.Register<my::SightEnemyCollisionAlgolithm>(my::CollisionAlgolithmType::kSightEnemyCollisionAlgolithm);
    collision_algolithm_factory.Register<my::EnemyAttackPlayerCollisionAlgolithm>(my::CollisionAlgolithmType::kEnemyAttackPlayerCollisionAlgolithm);
    collision_algolithm_factory.Register<my::EnemyBombGloveBulletCollisionAlgolithm>(my::CollisionAlgolithmType::kEnemyBombGloveBulletCollisionAlgolithm);
    collision_algolithm_factory.Register<my::EnemyPyrocitorBulletCollisionAlgolithm>(my::CollisionAlgolithmType::kEnemyPyrocitorBulletCollisionAlgolithm);
    collision_algolithm_factory.Register<my::EnemyBlasterBulletCollisionAlgolithm>(my::CollisionAlgolithmType::kEnemyBlasterBulletCollisionAlgolithm);
    collision_algolithm_factory.Register<my::EnemyBombGloveEffectCollisionAlgolithm>(my::CollisionAlgolithmType::kEnemyBombGloveEffectCollisionAlgolithm);
    collision_algolithm_factory.Register<my::BlasterBulletEnemyCollisionAlgolithm>(my::CollisionAlgolithmType::kBlasterBulletEnemyCollisionAlgolithm);
    collision_algolithm_factory.Register<my::BombGloveBulletEnemyCollisionAlgolithm>(my::CollisionAlgolithmType::kBombGloveBulletEnemyCollisionAlgolithm);

    this->GenerateLayer();
}

my::PhysicsWorld::~PhysicsWorld() {
    _layers.clear();
}

void my::PhysicsWorld::AddActor(const ActorPtr& actor) {
    std::vector<std::weak_ptr<my::CollisionComponent>> work;
    actor->GetComponents<my::CollisionComponent>(work);

    for (auto& ptr : work) {
        auto type = ptr.lock()->GetType();
        for (auto& layer : _layers) {
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
            if (layer.objects.empty()) {
                continue;
            } // if

            for (auto& target : layer.targets) {
                if (layer.targets.empty()) {
                    continue;
                } // if

                
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

void my::PhysicsWorld::Reset(void) {
    _layers.clear();
    this->GenerateLayer();
}