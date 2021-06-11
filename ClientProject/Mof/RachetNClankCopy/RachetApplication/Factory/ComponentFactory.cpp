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


rachet::ComponentFactory::ComponentFactory() :
    _component_creators() {
    rachet::ComponentFactory::AddComponentCreator<rachet::AIStateComponent>();
    rachet::ComponentFactory::AddComponentCreator<rachet::SightRecognitionComponent>();
    rachet::ComponentFactory::AddComponentCreator<rachet::ActionComponent>();
    rachet::ComponentFactory::AddComponentCreator<rachet::MotionComponent>();
    rachet::ComponentFactory::AddComponentCreator<rachet::HpComponent>();
    rachet::ComponentFactory::AddComponentCreator<rachet::InvincibleComponent>();
    rachet::ComponentFactory::AddComponentCreator<rachet::MotionStateComponent>();
    rachet::ComponentFactory::AddComponentCreator<rachet::VelocityComponent>();
    rachet::ComponentFactory::AddComponentCreator<rachet::TransformComponent>();
    rachet::ComponentFactory::AddComponentCreator<rachet::MeshComponent>();
    rachet::ComponentFactory::AddComponentCreator<rachet::BillboardComponent>();
    rachet::ComponentFactory::AddComponentCreator<rachet::AnimationMeshComponent>();
    rachet::ComponentFactory::AddComponentCreator<rachet::CameraComponent>();

#include "ComponentRegister/PlayerComponentRegister.h"
#include "ComponentRegister/EnemyComponentRegister.h"
#include "ComponentRegister/CollisionComponentRegister.h"
#include "ComponentRegister/OmniWrenchComponentRegister.h"
#include "ComponentRegister/ShipComponentRegister.h"
       
    rachet::ComponentFactory::AddComponentCreator<rachet::BoltCollisionComponent>();
    rachet::ComponentFactory::AddComponentCreator<rachet::BoltComponent>();
    rachet::ComponentFactory::AddComponentCreator<rachet::BoltActionStateComponent>();
    rachet::ComponentFactory::AddComponentCreator<rachet::BoltDefaultComponent>();
    rachet::ComponentFactory::AddComponentCreator<rachet::BoltMovedComponent>();
    rachet::ComponentFactory::AddComponentCreator<rachet::BoltGravitateComponent>();

    rachet::ComponentFactory::AddComponentCreator<rachet::BulletItemCollisionComponent>();
    rachet::ComponentFactory::AddComponentCreator<rachet::BulletItemComponent>();
    rachet::ComponentFactory::AddComponentCreator<rachet::BulletItemActionStateComponent>();
    rachet::ComponentFactory::AddComponentCreator<rachet::BulletItemDefaultComponent>();
    rachet::ComponentFactory::AddComponentCreator<rachet::BulletItemMovedComponent>();
    rachet::ComponentFactory::AddComponentCreator<rachet::BulletItemGravitateComponent>();

    rachet::ComponentFactory::AddComponentCreator<rachet::NanotechItemCollisionComponent>();
    rachet::ComponentFactory::AddComponentCreator<rachet::NanotechItemComponent>();
    rachet::ComponentFactory::AddComponentCreator<rachet::NanotechItemActionStateComponent>();
    rachet::ComponentFactory::AddComponentCreator<rachet::NanotechItemDefaultComponent>();
    rachet::ComponentFactory::AddComponentCreator<rachet::NanotechItemMovedComponent>();
    rachet::ComponentFactory::AddComponentCreator<rachet::NanotechItemGravitateComponent>();


    rachet::ComponentFactory::AddComponentCreator<rachet::BombGloveBulletComponent>();
    rachet::ComponentFactory::AddComponentCreator<rachet::BlasterBulletComponent>();
}

rachet::ComponentFactory::~ComponentFactory() {
}


bool rachet::ComponentFactory::Release(void) {
    for (auto& factory : _component_creators) {
        factory.second->Release();
        factory.second.reset();
    } // for
    _component_creators.clear();
    return true;
}

std::shared_ptr<rachet::Component> rachet::ComponentFactory::Create(const std::string& key, const rapidjson::Value& param) const {
    auto it = _component_creators.find(key);
    if (it != _component_creators.end()) {
        return it->second->Create(param);
    } // if
    return nullptr;
}