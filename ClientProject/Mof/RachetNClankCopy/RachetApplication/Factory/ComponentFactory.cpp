#include "ComponentFactory.h"

#include "My/Core/Utility.h"

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


my::ComponentFactory::ComponentFactory() :
    _component_creators() {
    my::ComponentFactory::AddComponentCreator<my::AIStateComponent>();
    my::ComponentFactory::AddComponentCreator<my::SightRecognitionComponent>();
    my::ComponentFactory::AddComponentCreator<my::ActionComponent>();
    my::ComponentFactory::AddComponentCreator<my::MotionComponent>();
    my::ComponentFactory::AddComponentCreator<my::HpComponent>();
    my::ComponentFactory::AddComponentCreator<my::InvincibleComponent>();
    my::ComponentFactory::AddComponentCreator<my::MotionStateComponent>();
    my::ComponentFactory::AddComponentCreator<my::VelocityComponent>();
    my::ComponentFactory::AddComponentCreator<my::TransformComponent>();
    my::ComponentFactory::AddComponentCreator<my::MeshComponent>();
    my::ComponentFactory::AddComponentCreator<my::BillboardComponent>();
    my::ComponentFactory::AddComponentCreator<my::AnimationMeshComponent>();
    my::ComponentFactory::AddComponentCreator<my::CameraComponent>();

#include "ComponentRegister/PlayerComponentRegister.h"
#include "ComponentRegister/EnemyComponentRegister.h"
#include "ComponentRegister/CollisionComponentRegister.h"
#include "ComponentRegister/OmniWrenchComponentRegister.h"
#include "ComponentRegister/ShipComponentRegister.h"
       
    my::ComponentFactory::AddComponentCreator<my::BoltCollisionComponent>();
    my::ComponentFactory::AddComponentCreator<my::BoltComponent>();
    my::ComponentFactory::AddComponentCreator<my::BoltActionStateComponent>();
    my::ComponentFactory::AddComponentCreator<my::BoltDefaultComponent>();
    my::ComponentFactory::AddComponentCreator<my::BoltMovedComponent>();
    my::ComponentFactory::AddComponentCreator<my::BoltGravitateComponent>();

    my::ComponentFactory::AddComponentCreator<my::BulletItemCollisionComponent>();
    my::ComponentFactory::AddComponentCreator<my::BulletItemComponent>();
    my::ComponentFactory::AddComponentCreator<my::BulletItemActionStateComponent>();
    my::ComponentFactory::AddComponentCreator<my::BulletItemDefaultComponent>();
    my::ComponentFactory::AddComponentCreator<my::BulletItemMovedComponent>();
    my::ComponentFactory::AddComponentCreator<my::BulletItemGravitateComponent>();

    my::ComponentFactory::AddComponentCreator<my::NanotechItemCollisionComponent>();
    my::ComponentFactory::AddComponentCreator<my::NanotechItemComponent>();
    my::ComponentFactory::AddComponentCreator<my::NanotechItemActionStateComponent>();
    my::ComponentFactory::AddComponentCreator<my::NanotechItemDefaultComponent>();
    my::ComponentFactory::AddComponentCreator<my::NanotechItemMovedComponent>();
    my::ComponentFactory::AddComponentCreator<my::NanotechItemGravitateComponent>();


    my::ComponentFactory::AddComponentCreator<my::BombGloveBulletComponent>();
    my::ComponentFactory::AddComponentCreator<my::BlasterBulletComponent>();
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