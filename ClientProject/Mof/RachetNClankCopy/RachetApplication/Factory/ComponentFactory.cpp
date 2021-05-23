#include "ComponentFactory.h"

#include "My/Core/Utility.h"

#include "../Component/AIStateComponent.h"
#include "../Component/SightRecognitionComponent.h"
#include "../Component/MotionComponent.h"
#include "../Component/HpComponent.h"
#include "../Component/InvincibleComponent.h"
#include "../Component/MotionStateComponent.h"
#include "../Component/VelocityComponent.h"
#include "../Component/TransformComponent.h"
#include "../Component/MeshComponent.h"
#include "../Component/CameraComponent.h"


#include "../Component/Player/PlayerComponentInclude.h"
#include "../Component/Enemy/EnemyComponentInclude.h"
#include "../Component/Collision/Object/CollisionComponentInclude.h"


#include "../Component/Weapon/OmniWrenchActionStateComponent.h"
#include "../Component/Weapon/OmniWrenchDefaultComponent.h"
#include "../Component/Weapon/OmniWrenchThrowedComponent.h"

#include "../Component/Bullet/BlasterBulletComponent.h"
#include "../Component/Bullet/BombGloveBulletComponent.h"
#include "../Component/Ship/ShipComponent.h"
#include "../Component/Ship/ShipMeshComponent.h"


my::ComponentFactory::ComponentFactory() :
    _component_creators() {
    my::ComponentFactory::AddComponentCreator<my::AIStateComponent>();
    my::ComponentFactory::AddComponentCreator<my::SightRecognitionComponent>();
    my::ComponentFactory::AddComponentCreator<my::MotionComponent>();
    my::ComponentFactory::AddComponentCreator<my::HpComponent>();
    my::ComponentFactory::AddComponentCreator<my::InvincibleComponent>();
    my::ComponentFactory::AddComponentCreator<my::MotionStateComponent>();
    my::ComponentFactory::AddComponentCreator<my::VelocityComponent>();
    my::ComponentFactory::AddComponentCreator<my::TransformComponent>();
    my::ComponentFactory::AddComponentCreator<my::MeshComponent>();
    my::ComponentFactory::AddComponentCreator<my::CameraComponent>();


#include "ComponentRegister/PlayerComponentRegister.h"
#include "ComponentRegister/EnemyComponentRegister.h"
#include "ComponentRegister/CollisionComponentRegister.h"
    
    my::ComponentFactory::AddComponentCreator<my::OmniWrenchActionStateComponent>();
    my::ComponentFactory::AddComponentCreator<my::OmniWrenchDefaultComponent>();
    my::ComponentFactory::AddComponentCreator<my::OmniWrenchThrowedComponent>();

    my::ComponentFactory::AddComponentCreator<my::BombGloveBulletComponent>();
    my::ComponentFactory::AddComponentCreator<my::BlasterBulletComponent>();
    my::ComponentFactory::AddComponentCreator<my::ShipComponent>();
    my::ComponentFactory::AddComponentCreator<my::ShipMeshComponent>();

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