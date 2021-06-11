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


ratchet::ComponentFactory::ComponentFactory() :
    _component_creators() {
    ratchet::ComponentFactory::AddComponentCreator<ratchet::AIStateComponent>();
    ratchet::ComponentFactory::AddComponentCreator<ratchet::SightRecognitionComponent>();
    ratchet::ComponentFactory::AddComponentCreator<ratchet::ActionComponent>();
    ratchet::ComponentFactory::AddComponentCreator<ratchet::MotionComponent>();
    ratchet::ComponentFactory::AddComponentCreator<ratchet::HpComponent>();
    ratchet::ComponentFactory::AddComponentCreator<ratchet::InvincibleComponent>();
    ratchet::ComponentFactory::AddComponentCreator<ratchet::MotionStateComponent>();
    ratchet::ComponentFactory::AddComponentCreator<ratchet::VelocityComponent>();
    ratchet::ComponentFactory::AddComponentCreator<ratchet::TransformComponent>();
    ratchet::ComponentFactory::AddComponentCreator<ratchet::MeshComponent>();
    ratchet::ComponentFactory::AddComponentCreator<ratchet::BillboardComponent>();
    ratchet::ComponentFactory::AddComponentCreator<ratchet::AnimationMeshComponent>();
    ratchet::ComponentFactory::AddComponentCreator<ratchet::CameraComponent>();

#include "ComponentRegister/PlayerComponentRegister.h"
#include "ComponentRegister/EnemyComponentRegister.h"
#include "ComponentRegister/CollisionComponentRegister.h"
#include "ComponentRegister/OmniWrenchComponentRegister.h"
#include "ComponentRegister/ShipComponentRegister.h"
       
    ratchet::ComponentFactory::AddComponentCreator<ratchet::BoltCollisionComponent>();
    ratchet::ComponentFactory::AddComponentCreator<ratchet::BoltComponent>();
    ratchet::ComponentFactory::AddComponentCreator<ratchet::BoltActionStateComponent>();
    ratchet::ComponentFactory::AddComponentCreator<ratchet::BoltDefaultComponent>();
    ratchet::ComponentFactory::AddComponentCreator<ratchet::BoltMovedComponent>();
    ratchet::ComponentFactory::AddComponentCreator<ratchet::BoltGravitateComponent>();

    ratchet::ComponentFactory::AddComponentCreator<ratchet::BulletItemCollisionComponent>();
    ratchet::ComponentFactory::AddComponentCreator<ratchet::BulletItemComponent>();
    ratchet::ComponentFactory::AddComponentCreator<ratchet::BulletItemActionStateComponent>();
    ratchet::ComponentFactory::AddComponentCreator<ratchet::BulletItemDefaultComponent>();
    ratchet::ComponentFactory::AddComponentCreator<ratchet::BulletItemMovedComponent>();
    ratchet::ComponentFactory::AddComponentCreator<ratchet::BulletItemGravitateComponent>();

    ratchet::ComponentFactory::AddComponentCreator<ratchet::NanotechItemCollisionComponent>();
    ratchet::ComponentFactory::AddComponentCreator<ratchet::NanotechItemComponent>();
    ratchet::ComponentFactory::AddComponentCreator<ratchet::NanotechItemActionStateComponent>();
    ratchet::ComponentFactory::AddComponentCreator<ratchet::NanotechItemDefaultComponent>();
    ratchet::ComponentFactory::AddComponentCreator<ratchet::NanotechItemMovedComponent>();
    ratchet::ComponentFactory::AddComponentCreator<ratchet::NanotechItemGravitateComponent>();


    ratchet::ComponentFactory::AddComponentCreator<ratchet::BombGloveBulletComponent>();
    ratchet::ComponentFactory::AddComponentCreator<ratchet::BlasterBulletComponent>();
}

ratchet::ComponentFactory::~ComponentFactory() {
}


bool ratchet::ComponentFactory::Release(void) {
    for (auto& factory : _component_creators) {
        factory.second->Release();
        factory.second.reset();
    } // for
    _component_creators.clear();
    return true;
}

std::shared_ptr<ratchet::Component> ratchet::ComponentFactory::Create(const std::string& key, const rapidjson::Value& param) const {
    auto it = _component_creators.find(key);
    if (it != _component_creators.end()) {
        return it->second->Create(param);
    } // if
    return nullptr;
}