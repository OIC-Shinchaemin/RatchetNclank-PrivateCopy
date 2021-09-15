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
#include "../Component/Collision/CollisionComponentInclude.h"
#include "../Component/Weapon/OmniWrench/OmniWrenchComponentInclude.h"
#include "../Component/Ship/ShipComponentInclude.h"
#include "../Component/Item/BoltComponentInclude.h"
#include "../Component/Item/BulletItem/BulletItemComponentInclude.h"
#include "../Component/Item/NanotechItem/NanotechItemComponentInclude.h"


#include "../Component/Scarecrow/ScarecrowComponent.h"
#include "../Component/Bullet/BlasterBulletComponent.h"
#include "../Component/Bullet/BombGloveBulletComponent.h"


ratchet::factory::ComponentFactory::ComponentFactory() :
    _component_creators() {
    ::ratchet::factory::ComponentFactory::AddComponentCreator<::ratchet::component::AIStateComponent>();
    ::ratchet::factory::ComponentFactory::AddComponentCreator<::ratchet::component::SightRecognitionComponent>();
    ::ratchet::factory::ComponentFactory::AddComponentCreator<::ratchet::component::ActionComponent>();
    ::ratchet::factory::ComponentFactory::AddComponentCreator<::ratchet::component::MotionComponent>();
    ::ratchet::factory::ComponentFactory::AddComponentCreator<::ratchet::component::HpComponent>();
    ::ratchet::factory::ComponentFactory::AddComponentCreator<::ratchet::component::InvincibleComponent>();
    ::ratchet::factory::ComponentFactory::AddComponentCreator<::ratchet::component::MotionStateComponent>();
    ::ratchet::factory::ComponentFactory::AddComponentCreator<::ratchet::component::VelocityComponent>();
    ::ratchet::factory::ComponentFactory::AddComponentCreator<::ratchet::component::TransformComponent>();
    ::ratchet::factory::ComponentFactory::AddComponentCreator<::ratchet::component::MeshComponent>();
    ::ratchet::factory::ComponentFactory::AddComponentCreator<::ratchet::component::BillboardComponent>();
    ::ratchet::factory::ComponentFactory::AddComponentCreator<::ratchet::component::AnimationMeshComponent>();
    ::ratchet::factory::ComponentFactory::AddComponentCreator<::ratchet::component::CameraComponent>();

#include "ComponentRegister/PlayerComponentRegister.h"
#include "ComponentRegister/EnemyComponentRegister.h"
#include "ComponentRegister/CollisionComponentRegister.h"
#include "ComponentRegister/OmniWrenchComponentRegister.h"
#include "ComponentRegister/ShipComponentRegister.h"

    ::ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::component::collision::BoltCollisionComponent>();
    ::ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::component::scarecrow::ScarecrowComponent>();
    ::ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::component::item::BoltComponent>();
    ::ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::component::item::BoltActionStateComponent>();
    ::ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::component::item::BoltDefaultComponent>();
    ::ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::component::item::BoltMovedComponent>();
    ::ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::component::item::BoltGravitateComponent>();

    ::ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::component::collision::BulletItemCollisionComponent>();
    ::ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::component::item::bulletitem::BulletItemComponent>();
    ::ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::component::item::bulletitem::BulletItemActionStateComponent>();
    ::ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::component::item::bulletitem::BulletItemDefaultComponent>();
    ::ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::component::item::bulletitem::BulletItemMovedComponent>();
    ::ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::component::item::bulletitem::BulletItemGravitateComponent>();
    
    ::ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::component::collision::NanotechItemCollisionComponent>();
    ::ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::component::item::nanotechitem::NanotechItemComponent>();
    ::ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::component::item::nanotechitem::NanotechItemActionStateComponent>();
    ::ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::component::item::nanotechitem::NanotechItemDefaultComponent>();
    ::ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::component::item::nanotechitem::NanotechItemMovedComponent>();
    ::ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::component::item::nanotechitem::NanotechItemGravitateComponent>();
    ::ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::component::bullet::BombGloveBulletComponent>();
    ::ratchet::factory::ComponentFactory::AddComponentCreator<ratchet::component::bullet::BlasterBulletComponent>();

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