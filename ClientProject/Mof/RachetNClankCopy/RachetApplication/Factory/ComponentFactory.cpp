#include "ComponentFactory.h"

#include "My/Core/Utility.h"

#include "../Component/AIStateComponent.h"
#include "../Component/SightRecognitionComponent.h"
#include "../Component/MotionComponent.h"
#include "../Component/HpComponent.h"
#include "../Component/InvincibleComponent.h"

#include "../Component/Player/PlayerComponent.h"
#include "../Component/Player/PlayerStateComponent.h"
#include "../Component/Player/PlayerIdleComponent.h"
#include "../Component/Player/PlayerMoveComponent.h"
#include "../Component/Player/PlayerJumpSetComponent.h"
#include "../Component/Player/PlayerJumpUpComponent.h"
#include "../Component/Player/PlayerJumpDownComponent.h"
#include "../Component/Player/PlayerJumpLandingComponent.h"
#include "../Component/Player/PlayerDoubleJumpComponent.h"
#include "../Component/Player/PlayerMeleeAttackOneComponent.h"
#include "../Component/Player/PlayerMeleeAttackOneEndComponent.h"
#include "../Component/Player/PlayerMeleeAttackTwoComponent.h"
#include "../Component/Player/PlayerMeleeAttackTwoEndComponent.h"
#include "../Component/Player/PlayerMeleeAttackThreeComponent.h"
#include "../Component/Player/PlayerMeleeAttackThreeEndComponent.h"
#include "../Component/Player/PlayerThrowAttackSetComponent.h"
#include "../Component/Player/PlayerThrowAttackComponent.h"
#include "../Component/Player/PlayerThrowAttackEndComponent.h"
#include "../Component/Player/PlayerJumpAttackSetComponent.h"
#include "../Component/Player/PlayerDamageComponent.h"
#include "../Component/Player/PlayerDeadComponent.h"
#include "../Component/Player/PlayerWeaponComponent.h"

#include "../Component/Enemy/EnemyComponent.h"
#include "../Component/Enemy/EnemyStateComponent.h"
#include "../Component/Enemy/EnemyIdleComponent.h"
#include "../Component/Enemy/EnemyMoveComponent.h"
#include "../Component/Enemy/EnemyGoHomeComponent.h"
#include "../Component/Enemy/EnemyMeleeAttackComponent.h"
#include "../Component/Enemy/EnemyRangedAttackComponent.h"
#include "../Component/Enemy/EnemyDamageComponent.h"

#include "../Component/Weapon/OmniWrenchActionStateComponent.h"
#include "../Component/Weapon/OmniWrenchDefaultComponent.h"
#include "../Component/Weapon/OmniWrenchThrowedComponent.h"


#include "../Component/Bullet/BlasterBulletComponent.h"
#include "../Component/Bullet/BombGloveBulletComponent.h"
#include "../Component/Ship/ShipComponent.h"
#include "../Component/Ship/ShipMeshComponent.h"
#include "../Component/MotionStateComponent.h"
#include "../Component/VelocityComponent.h"
#include "../Component/TransformComponent.h"
#include "../Component/MeshComponent.h"
#include "../Component/CameraComponent.h"
#include "../Component/Collision/Object/PlayerCollisionComponent.h"
//#include "../Component/Collision/Object/PlayerMeleeAttackCollisionComponent.h"
#include "../Component/Collision/Object/EnemyCollisionComponent.h"
#include "../Component/Collision/Object/SightCollisionComponent.h"
#include "../Component/Collision/Object/EnemyAttackCollisionComponent.h"
#include "../Component/Collision/Object/EnemyBulletCollisionComponent.h"
#include "../Component/Collision/Object/OmniWrenchCollisionComponent.h"
#include "../Component/Collision/Object/BombGloveBulletCollisionComponent.h"
#include "../Component/Collision/Object/PyrocitorBulletCollisionComponent.h"
#include "../Component/Collision/Object/BlasterBulletCollisionComponent.h"
#include "../Component/Collision/Object/BombGloveEffectCollisionComponent.h"
#include "../Component/Collision/Object/ShipCollisionComponent.h"
#include "../Component/Collision/Object/WaterFlowCollisionComponent.h"
#include "../Component/Collision/Object/CameraCollisionComponent.h"


my::ComponentFactory::ComponentFactory() :
    _component_creators() {
    my::ComponentFactory::AddComponentCreator<my::AIStateComponent>();
    my::ComponentFactory::AddComponentCreator<my::SightRecognitionComponent>();
    my::ComponentFactory::AddComponentCreator<my::MotionComponent>();
    my::ComponentFactory::AddComponentCreator<my::HpComponent>();
    my::ComponentFactory::AddComponentCreator<my::PlayerComponent>();
    my::ComponentFactory::AddComponentCreator<my::PlayerStateComponent>();
    my::ComponentFactory::AddComponentCreator<my::PlayerIdleComponent>();
    my::ComponentFactory::AddComponentCreator<my::PlayerMoveComponent>();
    my::ComponentFactory::AddComponentCreator<my::PlayerJumpSetComponent>();
    my::ComponentFactory::AddComponentCreator<my::PlayerJumpUpComponent>();
    my::ComponentFactory::AddComponentCreator<my::PlayerJumpDownComponent>();
    my::ComponentFactory::AddComponentCreator<my::PlayerJumpLandingComponent>();
    my::ComponentFactory::AddComponentCreator<my::PlayerDoubleJumpComponent>();
    my::ComponentFactory::AddComponentCreator<my::PlayerMeleeAttackOneComponent>();
    my::ComponentFactory::AddComponentCreator<my::PlayerMeleeAttackOneEndComponent>();
    my::ComponentFactory::AddComponentCreator<my::PlayerMeleeAttackTwoComponent>();
    my::ComponentFactory::AddComponentCreator<my::PlayerMeleeAttackTwoEndComponent>();
    my::ComponentFactory::AddComponentCreator<my::PlayerMeleeAttackThreeComponent>();
    my::ComponentFactory::AddComponentCreator<my::PlayerMeleeAttackThreeEndComponent>();
    my::ComponentFactory::AddComponentCreator<my::PlayerThrowAttackSetComponent>();
    my::ComponentFactory::AddComponentCreator<my::PlayerThrowAttackComponent>();
    my::ComponentFactory::AddComponentCreator<my::PlayerThrowAttackEndComponent>();

    my::ComponentFactory::AddComponentCreator<my::PlayerJumpAttackSetComponent>();

    my::ComponentFactory::AddComponentCreator<my::PlayerDamageComponent>();
    my::ComponentFactory::AddComponentCreator<my::PlayerDeadComponent>();
    my::ComponentFactory::AddComponentCreator<my::PlayerWeaponComponent>();
    my::ComponentFactory::AddComponentCreator<my::InvincibleComponent>();
    my::ComponentFactory::AddComponentCreator<my::EnemyComponent>();
    my::ComponentFactory::AddComponentCreator<my::EnemyStateComponent>();
    my::ComponentFactory::AddComponentCreator<my::EnemyIdleComponent>();
    my::ComponentFactory::AddComponentCreator<my::EnemyMoveComponent>();
    my::ComponentFactory::AddComponentCreator<my::EnemyGoHomeComponent>();
    my::ComponentFactory::AddComponentCreator<my::EnemyMeleeAttackComponent>();
    my::ComponentFactory::AddComponentCreator<my::EnemyRangedAttackComponent>();
    my::ComponentFactory::AddComponentCreator<my::EnemyDamageComponent>();

    my::ComponentFactory::AddComponentCreator<my::OmniWrenchActionStateComponent>();
    my::ComponentFactory::AddComponentCreator<my::OmniWrenchDefaultComponent>();
    my::ComponentFactory::AddComponentCreator<my::OmniWrenchThrowedComponent>();

    my::ComponentFactory::AddComponentCreator<my::BombGloveBulletComponent>();
    my::ComponentFactory::AddComponentCreator<my::BlasterBulletComponent>();
    my::ComponentFactory::AddComponentCreator<my::ShipComponent>();
    my::ComponentFactory::AddComponentCreator<my::ShipMeshComponent>();
    my::ComponentFactory::AddComponentCreator<my::MotionStateComponent>();
    my::ComponentFactory::AddComponentCreator<my::VelocityComponent>();
    my::ComponentFactory::AddComponentCreator<my::TransformComponent>();
    my::ComponentFactory::AddComponentCreator<my::MeshComponent>();
    my::ComponentFactory::AddComponentCreator<my::CameraComponent>();
    my::ComponentFactory::AddComponentCreator<my::PlayerCollisionComponent>();
    //my::ComponentFactory::AddComponentCreator<my::PlayerMeleeAttackCollisionComponent>();
    my::ComponentFactory::AddComponentCreator<my::EnemyCollisionComponent>();
    my::ComponentFactory::AddComponentCreator<my::SightCollisionComponent>();
    my::ComponentFactory::AddComponentCreator<my::EnemyAttackCollisionComponent>();
    my::ComponentFactory::AddComponentCreator<my::EnemyBulletCollisionComponent>();
    my::ComponentFactory::AddComponentCreator<my::OmniWrenchCollisionComponent>();
    my::ComponentFactory::AddComponentCreator<my::BombGloveBulletCollisionComponent>();
    my::ComponentFactory::AddComponentCreator<my::PyrocitorBulletCollisionComponent>();
    my::ComponentFactory::AddComponentCreator<my::BlasterBulletCollisionComponent>();
    my::ComponentFactory::AddComponentCreator<my::BombGloveEffectCollisionComponent>();
    my::ComponentFactory::AddComponentCreator<my::ShipCollisionComponent>();
    my::ComponentFactory::AddComponentCreator<my::WaterFlowCollisionComponent>();
    my::ComponentFactory::AddComponentCreator<my::CameraCollisionComponent>();
}

my::ComponentFactory::~ComponentFactory() {
}


bool my::ComponentFactory::Release(void) {
    for (auto& factory : _component_creators) {
        factory.second->Release();
        factory.second.reset();
    } // for
    _component_creators.clear();
    return true;
}

std::shared_ptr<my::Component> my::ComponentFactory::Create(const std::string& key, const rapidjson::Value& param) const {
    auto it = _component_creators.find(key);
    if (it != _component_creators.end()) {
        return it->second->Create(param);
    } // if
    return nullptr;
}