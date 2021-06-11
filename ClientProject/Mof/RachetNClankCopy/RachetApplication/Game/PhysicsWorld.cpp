#include "PhysicsWorld.h"

#include "Base/Core/Utility.h"
#include "../Component/Collision/Algolithm/CollisionAlgolithmDefine.h"
#include "../Component/Collision/Algolithm/PlayerEnemyCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/PlayerEnemyMeleeAttackCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/PlayerEnemyBulletCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/PlayerShipCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/PlayerWaterFlowCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/PlayerNanotechItemCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/EnemyEnemyCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/EnemyPlayerCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/EnemyOmniWrenchCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/SightPlayerCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/SightEnemyCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/EnemyMeleeAttackPlayerCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/EnemyOmniWrenchCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/EnemyBombGloveBulletCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/EnemyPyrocitorBulletCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/EnemyBlasterBulletCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/EnemyBombGloveEffectCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/BlasterBulletEnemyCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/BombGloveBulletEnemyCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/ShipPlayerCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/BoltPlayerCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/BulletItemPlayerCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/NanotechItemPlayerCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/PlayerShopCollisionAlgolithm.h"
#include "../Component/Collision/Object/CollisionComponentDefine.h"


void rachet::PhysicsWorld::GenerateLayer(void) {
    const char* types[] = {
      rachet::CollisionAlgolithmType::kPlayerEnemyCollisionAlgolithm.c_str(),
      rachet::CollisionAlgolithmType::kPlayerEnemyMeleeAttackCollisionAlgolithm.c_str(),
      rachet::CollisionAlgolithmType::kPlayerEnemyBulletCollisionAlgolithm.c_str(),
      rachet::CollisionAlgolithmType::kPlayerShipCollisionAlgolithm.c_str(),
      rachet::CollisionAlgolithmType::kPlayerWaterFlowCollisionAlgolithm.c_str(),
      rachet::CollisionAlgolithmType::kPlayerNanotechItemCollisionAlgolithm.c_str(),
      rachet::CollisionAlgolithmType::kEnemyEnemyCollisionAlgolithm.c_str(),
      rachet::CollisionAlgolithmType::kEnemyPlayerCollisionAlgolithm.c_str(),
      rachet::CollisionAlgolithmType::kEnemyOmniWrenchAttackCollisionAlgolithm.c_str(),
      rachet::CollisionAlgolithmType::kSightPlayerCollisionAlgolithm.c_str(),
      rachet::CollisionAlgolithmType::kSightEnemyCollisionAlgolithm.c_str(),
      rachet::CollisionAlgolithmType::kEnemyMeleeAttackPlayerCollisionAlgolithm.c_str(),
      rachet::CollisionAlgolithmType::kEnemyOmniWrenchCollisionAlgolithm.c_str(),
      rachet::CollisionAlgolithmType::kEnemyBombGloveBulletCollisionAlgolithm.c_str(),
      rachet::CollisionAlgolithmType::kEnemyPyrocitorBulletCollisionAlgolithm.c_str(),
      rachet::CollisionAlgolithmType::kEnemyBlasterBulletCollisionAlgolithm.c_str(),
      rachet::CollisionAlgolithmType::kEnemyBombGloveEffectCollisionAlgolithm.c_str(),
      rachet::CollisionAlgolithmType::kBlasterBulletEnemyCollisionAlgolithm.c_str(),
      rachet::CollisionAlgolithmType::kBombGloveBulletEnemyCollisionAlgolithm.c_str(),
      rachet::CollisionAlgolithmType::kShipPlayerCollisionAlgolithm.c_str(),
      rachet::CollisionAlgolithmType::kBoltPlayerCollisionAlgolithm.c_str(),
      rachet::CollisionAlgolithmType::kBulletItemPlayerCollisionAlgolithm.c_str(),
      rachet::CollisionAlgolithmType::kNanotechItemPlayerCollisionAlgolithm.c_str(),
      rachet::CollisionAlgolithmType::kPlayerShopCollisionAlgolithm.c_str(),
    };


    for (auto type : types) {
        auto temp = CollisionLayer();
        temp.algo = collision_algolithm_factory.Create(type);
        _layers.push_back(temp);
    } // for
}

rachet::PhysicsWorld::PhysicsWorld() :
    _layers() {
    collision_algolithm_factory.Register<rachet::PlayerEnemyCollisionAlgolithm>(rachet::CollisionAlgolithmType::kPlayerEnemyCollisionAlgolithm);
    collision_algolithm_factory.Register<rachet::PlayerEnemyMeleeAttackCollisionAlgolithm>(rachet::CollisionAlgolithmType::kPlayerEnemyMeleeAttackCollisionAlgolithm);
    collision_algolithm_factory.Register<rachet::PlayerEnemyBulletCollisionAlgolithm>(rachet::CollisionAlgolithmType::kPlayerEnemyBulletCollisionAlgolithm);
    collision_algolithm_factory.Register<rachet::PlayerShipCollisionAlgolithm>(rachet::CollisionAlgolithmType::kPlayerShipCollisionAlgolithm);
    collision_algolithm_factory.Register<rachet::PlayerWaterFlowCollisionAlgolithm>(rachet::CollisionAlgolithmType::kPlayerWaterFlowCollisionAlgolithm);
    collision_algolithm_factory.Register<rachet::PlayerNanotechItemCollisionAlgolithm>(rachet::CollisionAlgolithmType::kPlayerNanotechItemCollisionAlgolithm);
    collision_algolithm_factory.Register<rachet::EnemyEnemyCollisionAlgolithm>(rachet::CollisionAlgolithmType::kEnemyEnemyCollisionAlgolithm);
    collision_algolithm_factory.Register<rachet::EnemyPlayerCollisionAlgolithm>(rachet::CollisionAlgolithmType::kEnemyPlayerCollisionAlgolithm);
    collision_algolithm_factory.Register<rachet::EnemyOmniWrenchCollisionAlgolithm>(rachet::CollisionAlgolithmType::kEnemyOmniWrenchAttackCollisionAlgolithm);
    collision_algolithm_factory.Register<rachet::SightPlayerCollisionAlgolithm>(rachet::CollisionAlgolithmType::kSightPlayerCollisionAlgolithm);
    collision_algolithm_factory.Register<rachet::SightEnemyCollisionAlgolithm>(rachet::CollisionAlgolithmType::kSightEnemyCollisionAlgolithm);
    collision_algolithm_factory.Register<rachet::EnemyMeleeAttackPlayerCollisionAlgolithm>(rachet::CollisionAlgolithmType::kEnemyMeleeAttackPlayerCollisionAlgolithm);
    collision_algolithm_factory.Register<rachet::EnemyOmniWrenchCollisionAlgolithm>(rachet::CollisionAlgolithmType::kEnemyOmniWrenchCollisionAlgolithm);
    collision_algolithm_factory.Register<rachet::EnemyBombGloveBulletCollisionAlgolithm>(rachet::CollisionAlgolithmType::kEnemyBombGloveBulletCollisionAlgolithm);
    collision_algolithm_factory.Register<rachet::EnemyPyrocitorBulletCollisionAlgolithm>(rachet::CollisionAlgolithmType::kEnemyPyrocitorBulletCollisionAlgolithm);
    collision_algolithm_factory.Register<rachet::EnemyBlasterBulletCollisionAlgolithm>(rachet::CollisionAlgolithmType::kEnemyBlasterBulletCollisionAlgolithm);
    collision_algolithm_factory.Register<rachet::EnemyBombGloveEffectCollisionAlgolithm>(rachet::CollisionAlgolithmType::kEnemyBombGloveEffectCollisionAlgolithm);
    collision_algolithm_factory.Register<rachet::BlasterBulletEnemyCollisionAlgolithm>(rachet::CollisionAlgolithmType::kBlasterBulletEnemyCollisionAlgolithm);
    collision_algolithm_factory.Register<rachet::BombGloveBulletEnemyCollisionAlgolithm>(rachet::CollisionAlgolithmType::kBombGloveBulletEnemyCollisionAlgolithm);
    collision_algolithm_factory.Register<rachet::ShipPlayerCollisionAlgolithm>(rachet::CollisionAlgolithmType::kShipPlayerCollisionAlgolithm);
    collision_algolithm_factory.Register<rachet::BoltPlayerCollisionAlgolithm>(rachet::CollisionAlgolithmType::kBoltPlayerCollisionAlgolithm);
    collision_algolithm_factory.Register<rachet::BulletItemPlayerCollisionAlgolithm>(rachet::CollisionAlgolithmType::kBulletItemPlayerCollisionAlgolithm);
    collision_algolithm_factory.Register<rachet::NanotechItemPlayerCollisionAlgolithm>(rachet::CollisionAlgolithmType::kNanotechItemPlayerCollisionAlgolithm);
    collision_algolithm_factory.Register<rachet::PlayerShopCollisionAlgolithm>(rachet::CollisionAlgolithmType::kPlayerShopCollisionAlgolithm);

    this->GenerateLayer();
}

rachet::PhysicsWorld::~PhysicsWorld() {
    _layers.clear();
}

void rachet::PhysicsWorld::AddActor(const ActorPtr& actor) {
    std::vector<std::weak_ptr<rachet::CollisionComponent>> work;
    actor->GetComponents<rachet::CollisionComponent>(work);

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

    for (auto& ptr : work) {
        _list_for_stage.push_back(ptr.lock());
    } // for
}

void rachet::PhysicsWorld::RemoveActor(const ActorPtr& actor) {
    std::vector<std::weak_ptr<rachet::CollisionComponent>> work;
    actor->GetComponents<rachet::CollisionComponent>(work);

    for (auto& ptr : work) {
        for (auto& layer : _layers) {
            ut::EraseRemove(layer.objects, ptr.lock());
            ut::EraseRemove(layer.targets, ptr.lock());
        } // for
    } // for
    for (auto& ptr : work) {
        ut::EraseRemove(_list_for_stage, ptr.lock());
    } // for
}

bool rachet::PhysicsWorld::Update(void) {
    for (auto& layer : _layers) {
        for (auto& object : layer.objects) {
            if (!object->IsActive()) {
                continue;
            } // if
            if (object->IsSleep()) {
                continue;
            } // if
            
            for (auto& target : layer.targets) {
                if (!target->IsActive()) {
                    continue;
                } // if
                if (target->IsSleep()) {
                    continue;
                } // if

                if (object == target) {
                    continue;
                } // if
                auto info = rachet::CollisionInfo();
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

void rachet::PhysicsWorld::CollisionStage(Stage* stage) {
    auto meshes = stage->GetMeshArray();

    auto objs = stage->GetStaticObjectArray();
    for (auto obj : objs) {
        if (!obj->IsCollisionEnable()) {
            continue;
        } // if

        int mesh_no = obj->GetMeshNo();
        for (auto com : _list_for_stage) {
            if (com->IsSleep()) {
                continue;
            } // if
            auto mesh = meshes.at(mesh_no);
            com->CollisionStage(&*mesh, *obj);
        } // for
    } // for


    auto gimmicks = stage->GetGimmickArray();
    for (auto gimmick : gimmicks) {
        int mesh_no = gimmick->GetMeshNo();

        for (auto com : _list_for_stage) {
            auto mesh = meshes.at(mesh_no);
            com->CollisionStageGimmick(&*mesh, gimmick);
        } // for
    } // for
}

void rachet::PhysicsWorld::Reset(void) {
    _layers.clear();
    _list_for_stage.clear();
    this->GenerateLayer();
}