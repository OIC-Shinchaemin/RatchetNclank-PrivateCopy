#include "ComponentFactory.h"

#include "Base/Core/Utility.h"

#include "../Component/AIStateComponent.h"
#include "../Component/SightRecognitionComponent.h"
#include "../Component/ActionComponent.h"
#include "../Component/MotionComponent.h"
#include "../Component/HpComponent.h"
#include "../Component/InvincibleComponent.h"
#include "../Component/MotionStateComponent.h"
#include "../Component/VelocityComponent.h"
#include "../Component/TransformComponent.h"
#include "../Component/MeshComponent.h"
#include "../Component/BillboardComponent.h"
#include "../Component/AnimationMeshComponent.h"
#include "../Component/CameraComponent.h"


#include "../Component/Player/PlayerComponentInclude.h"
#include "../Component/Enemy/EnemyComponentInclude.h"
#include "../Component/Collision/Object/CollisionComponentInclude.h"
#include "../Component/Weapon/OmniWrench/OmniWrenchComponentInclude.h"
#include "../Component/Ship/ShipComponentInclude.h"
#include "../Component/Item/BoltComponentInclude.h"
#include "../Component/Item/BulletItem/BulletItemComponentInclude.h"
#include "../Component/Item/NanotechItem/NanotechItemComponentInclude.h"

#include "../Component/Bullet/BlasterBulletComponent.h"
#include "../Component/Bullet/BombGloveBulletComponent.h"


ratchet::factory::ComponentFactory::ComponentFactory() :
    _component_creators() {
    ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::AIStateComponent>();
    ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::SightRecognitionComponent>();
    ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::ActionComponent>();
    ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::MotionComponent>();
    ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::HpComponent>();
    ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::InvincibleComponent>();
    ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::MotionStateComponent>();
    ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::VelocityComponent>();
    ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::TransformComponent>();
    ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::MeshComponent>();
    ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::BillboardComponent>();
    ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::AnimationMeshComponent>();
    ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::CameraComponent>();

#include "ComponentRegister/PlayerComponentRegister.h"
#include "ComponentRegister/EnemyComponentRegister.h"
#include "ComponentRegister/CollisionComponentRegister.h"
#include "ComponentRegister/OmniWrenchComponentRegister.h"
#include "ComponentRegister/ShipComponentRegister.h"
       
    ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::BoltCollisionComponent>();
    ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::BoltComponent>();
    ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::BoltActionStateComponent>();
    ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::BoltDefaultComponent>();
    ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::BoltMovedComponent>();
    ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::BoltGravitateComponent>();

    ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::BulletItemCollisionComponent>();
    ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::BulletItemComponent>();
    ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::BulletItemActionStateComponent>();
    ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::BulletItemDefaultComponent>();
    ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::BulletItemMovedComponent>();
    ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::BulletItemGravitateComponent>();

    ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::NanotechItemCollisionComponent>();
    ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::NanotechItemComponent>();
    ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::NanotechItemActionStateComponent>();
    ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::NanotechItemDefaultComponent>();
    ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::NanotechItemMovedComponent>();
    ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::NanotechItemGravitateComponent>();


    ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::BombGloveBulletComponent>();
    ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::BlasterBulletComponent>();
}

ratchet::factory::ComponentFactory::~ComponentFactory() {
}


bool ratchet::factory::ComponentFactory::Release(void) {
    for (auto& factory : _component_creators) {
        factory.second->Release();
        factory.second.reset();
    } // for
    _component_creators.clear();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::factory::ComponentFactory::Create(const std::string& key, const rapidjson::Value& param) const {
    auto it = _component_creators.find(key);
    if (it != _component_creators.end()) {
        return it->second->Create(param);
    } // if
    return nullptr;
}