#include "PhysicsWorld.h"

#include "Base/Core/Utility.h"
#include "../Component/Collision/CollisionAlgolithmDefine.h"
#include "../Component/Collision/CollisionComponentDefine.h"
#include "../Component/Collision/CollisionAlgolithmInclude.h"


void ratchet::game::PhysicsWorld::GenerateLayer(void) {
    const char* types[] = {

        ratchet::CollisionAlgolithmType::kBlasterBulletEnemyCollisionAlgolithm.c_str(),
        ratchet::CollisionAlgolithmType::kBombGloveBulletEnemyCollisionAlgolithm.c_str(),

        ratchet::CollisionAlgolithmType::kBlasterBulletScarecrowCollisionAlgolithm.c_str(),
        ratchet::CollisionAlgolithmType::kBombGloveBulletScarecrowCollisionAlgolithm.c_str(),

        ratchet::CollisionAlgolithmType::kBoltPlayerCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kBulletItemPlayerCollisionAlgolithm.c_str(),


      ratchet::CollisionAlgolithmType::kEnemyEnemyCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kEnemyPlayerCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kEnemyOmniWrenchCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kEnemyBombGloveBulletCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kEnemyPyrocitorBulletCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kEnemyBlasterBulletCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kEnemyBombGloveEffectCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kEnemyMeleeAttackPlayerCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kEnemyOmniWrenchCollisionAlgolithm.c_str(),


      ratchet::CollisionAlgolithmType::kNanotechItemPlayerCollisionAlgolithm.c_str(),
      
      ratchet::CollisionAlgolithmType::kKingPlayerCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kQueenPlayerCollisionAlgolithm.c_str(),



      ratchet::CollisionAlgolithmType::kPlayerBarricadeCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kPlayerBarrackCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kPlayerFenceCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kPlayerEnemyCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kPlayerEnemyMeleeAttackCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kPlayerEnemyBulletCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kPlayerKingCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kPlayerScarecrowCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kPlayerShipCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kPlayerWaterFlowCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kPlayerNanotechItemCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kPlayerShopCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kPlayerWallCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kPlayerQueenCollisionAlgolithm.c_str(),

      ratchet::CollisionAlgolithmType::kScarecrowBlasterBulletCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kScarecrowBombGloveBulletCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kScarecrowBombGloveEffectCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kScarecrowOmniWrenchCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kScarecrowPyrocitorBulletCollisionAlgolithm.c_str(),

      ratchet::CollisionAlgolithmType::kShipPlayerCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kSightPlayerCollisionAlgolithm.c_str(),
      ratchet::CollisionAlgolithmType::kSightEnemyCollisionAlgolithm.c_str(),
    };


    for (auto type : types) {
        auto temp = CollisionLayer();
        temp.algo = collision_algolithm_factory.Create(type);
        _layers.push_back(temp);
    } // for
}

ratchet::game::PhysicsWorld::PhysicsWorld() :
    _layers() {
    collision_algolithm_factory.Register<ratchet::BlasterBulletEnemyCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kBlasterBulletEnemyCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::BlasterBulletScarecrowCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kBlasterBulletScarecrowCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::BombGloveBulletEnemyCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kBombGloveBulletEnemyCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::BombGloveBulletScarecrowCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kBombGloveBulletScarecrowCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::BoltPlayerCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kBoltPlayerCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::BulletItemPlayerCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kBulletItemPlayerCollisionAlgolithm);


    collision_algolithm_factory.Register<ratchet::EnemyEnemyCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kEnemyEnemyCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::EnemyPlayerCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kEnemyPlayerCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::EnemyOmniWrenchCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kEnemyOmniWrenchCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::EnemyMeleeAttackPlayerCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kEnemyMeleeAttackPlayerCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::EnemyOmniWrenchCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kEnemyOmniWrenchCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::EnemyBombGloveBulletCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kEnemyBombGloveBulletCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::EnemyPyrocitorBulletCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kEnemyPyrocitorBulletCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::EnemyBlasterBulletCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kEnemyBlasterBulletCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::EnemyBombGloveEffectCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kEnemyBombGloveEffectCollisionAlgolithm);

    collision_algolithm_factory.Register<ratchet::NanotechItemPlayerCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kNanotechItemPlayerCollisionAlgolithm);

    collision_algolithm_factory.Register<ratchet::KingPlayerCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kKingPlayerCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::QueenPlayerCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kQueenPlayerCollisionAlgolithm);

    collision_algolithm_factory.Register<ratchet::ScarecrowBlasterBulletCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kScarecrowBlasterBulletCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::ScarecrowBombGloveBulletCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kScarecrowBombGloveBulletCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::ScarecrowBombGloveEffectCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kScarecrowBombGloveEffectCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::ScarecrowOmniWrenchCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kScarecrowOmniWrenchCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::ScarecrowPyrocitorBulletCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kScarecrowPyrocitorBulletCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::SightPlayerCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kSightPlayerCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::SightEnemyCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kSightEnemyCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::ShipPlayerCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kShipPlayerCollisionAlgolithm);

    collision_algolithm_factory.Register<ratchet::PlayerFenceCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kPlayerFenceCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::PlayerBarrackCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kPlayerBarrackCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::PlayerBarricadeCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kPlayerBarricadeCollisionAlgolithm);

    collision_algolithm_factory.Register<ratchet::PlayerEnemyCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kPlayerEnemyCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::PlayerEnemyMeleeAttackCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kPlayerEnemyMeleeAttackCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::PlayerEnemyBulletCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kPlayerEnemyBulletCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::PlayerKingCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kPlayerKingCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::PlayerQueenCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kPlayerQueenCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::PlayerScarecrowCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kPlayerScarecrowCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::PlayerShipCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kPlayerShipCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::PlayerWaterFlowCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kPlayerWaterFlowCollisionAlgolithm);
    collision_algolithm_factory.Register<ratchet::PlayerNanotechItemCollisionAlgolithm>(ratchet::CollisionAlgolithmType::kPlayerNanotechItemCollisionAlgolithm);
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