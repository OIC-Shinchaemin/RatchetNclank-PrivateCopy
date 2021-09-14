#include "PhysicsWorld.h"

#include "Base/Core/Utility.h"
#include "../Component/Collision/CollisionAlgolithmDefine.h"
#include "../Component/Collision/Algolithm/PlayerEnemyCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/PlayerEnemyMeleeAttackCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/PlayerEnemyBulletCollisionAlgolithm.h"
#include "../Component/Collision/Algolithm/PlayerKingCollisionAlgolithm.h"
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
#include "../Component/Collision/Algolithm/PlayerWallCollisionAlgolithm.h"
#include "../Component/Collision/CollisionComponentDefine.h"


void ratchet::game::PhysicsWorld::GenerateLayer(void) {
    const char* types[] = {
      ratchet::CollisionAlgolithmType::kPlayerEnemyCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kPlayerEnemyMeleeAttackCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kPlayerEnemyBulletCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kPlayerKingCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kPlayerShipCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kPlayerWaterFlowCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kPlayerNanotechItemCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kEnemyEnemyCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kEnemyPlayerCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kEnemyOmniWrenchAttackCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kSightPlayerCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kSightEnemyCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kEnemyMeleeAttackPlayerCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kEnemyOmniWrenchCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kEnemyBombGloveBulletCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kEnemyPyrocitorBulletCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kEnemyBlasterBulletCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kEnemyBombGloveEffectCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kBlasterBulletEnemyCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kBombGloveBulletEnemyCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kShipPlayerCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kBoltPlayerCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kBulletItemPlayerCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kNanotechItemPlayerCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kPlayerShopCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kPlayerWallCollisionAlgolithm.c_str(),
    };


    for (auto type : types) {
        auto temp = CollisionLayer();
        temp.algo = collision_algolithm_factory.Create(type);
        _layers.push_back(temp);
    } // for
}

ratchet::game::PhysicsWorld::PhysicsWorld() :
    _layers() {
    collision_algolithm_factory.Register<ratchet::PlayerEnemyCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kPlayerEnemyCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::PlayerEnemyMeleeAttackCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kPlayerEnemyMeleeAttackCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::PlayerEnemyBulletCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kPlayerEnemyBulletCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::PlayerKingCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kPlayerKingCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::PlayerShipCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kPlayerShipCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::PlayerWaterFlowCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kPlayerWaterFlowCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::PlayerNanotechItemCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kPlayerNanotechItemCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::EnemyEnemyCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kEnemyEnemyCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::EnemyPlayerCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kEnemyPlayerCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::EnemyOmniWrenchCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kEnemyOmniWrenchAttackCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::SightPlayerCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kSightPlayerCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::SightEnemyCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kSightEnemyCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::EnemyMeleeAttackPlayerCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kEnemyMeleeAttackPlayerCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::EnemyOmniWrenchCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kEnemyOmniWrenchCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::EnemyBombGloveBulletCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kEnemyBombGloveBulletCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::EnemyPyrocitorBulletCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kEnemyPyrocitorBulletCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::EnemyBlasterBulletCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kEnemyBlasterBulletCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::EnemyBombGloveEffectCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kEnemyBombGloveEffectCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::BlasterBulletEnemyCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kBlasterBulletEnemyCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::BombGloveBulletEnemyCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kBombGloveBulletEnemyCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::ShipPlayerCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kShipPlayerCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::BoltPlayerCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kBoltPlayerCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::BulletItemPlayerCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kBulletItemPlayerCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::NanotechItemPlayerCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kNanotechItemPlayerCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::PlayerShopCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kPlayerShopCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::PlayerWallCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kPlayerWallCollisionAlgolithm);
    this->GenerateLayer();
}

ratchet::game::PhysicsWorld::~PhysicsWorld() {
    _layers.clear();
}

void ratchet::game::PhysicsWorld::AddActor(const ActorPtr& actor) {
    std::vector<std::weak_ptr<ratchet::component::collision::CollisionComponent>> work;
    actor->GetComponents<ratchet::component::collision::CollisionComponent>(work);

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

void ratchet::game::PhysicsWorld::RemoveActor(const ActorPtr& actor) {
    std::vector<std::weak_ptr<ratchet::component::collision::CollisionComponent>> work;
    actor->GetComponents<ratchet::component::collision::CollisionComponent>(work);

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

bool ratchet::game::PhysicsWorld::Update(void) {
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
                auto info = component::collision::CollisionInfo();
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

void ratchet::game::PhysicsWorld::CollisionStage(Stage* stage) {
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

void ratchet::game::PhysicsWorld::Reset(void) {
    _layers.clear();
    _list_for_stage.clear();
    this->GenerateLayer();
}