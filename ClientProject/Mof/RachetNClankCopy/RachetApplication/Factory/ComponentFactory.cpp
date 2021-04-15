#include "ComponentFactory.h"

#include "My/Core/Utility.h"

#include "../Component/AIStateComponent.h"
#include "../Component/SightRecognitionComponent.h"
#include "../Component/MotionComponent.h"
#include "../Component/HpComponent.h"
#include "../Component/Player/PlayerIdleComponent.h"
#include "../Component/Player/PlayerMoveComponent.h"
#include "../Component/Enemy/EnemyStateComponent.h"
#include "../Component/Enemy/EnemyIdleComponent.h"
#include "../Component/Enemy/EnemyMoveComponent.h"
#include "../Component/Enemy/EnemyAttackComponent.h"
#include "../Component/MotionStateComponent.h"
#include "../Component/VelocityComponent.h"
#include "../Component/TransformComponent.h"
#include "../Component/MeshComponent.h"
#include "../Component/Collision/Object/PlayerCollisionObject.h"
#include "../Component/Collision/Object/EnemyCollisionObject.h"
#include "../Component/Collision/Object/EnemySightCollisionObject.h"


my::ComponentFactory::ComponentFactory() :
    _component_creators() {
    my::ComponentFactory::AddComponentCreator<my::AIStateComponent>();
    my::ComponentFactory::AddComponentCreator<my::SightRecognitionComponent>();
    my::ComponentFactory::AddComponentCreator<my::MotionComponent>();
    my::ComponentFactory::AddComponentCreator<my::HpComponent>();
    my::ComponentFactory::AddComponentCreator<my::PlayerIdleComponent>();
    my::ComponentFactory::AddComponentCreator<my::PlayerMoveComponent>();
    my::ComponentFactory::AddComponentCreator<my::EnemyStateComponent>();
    my::ComponentFactory::AddComponentCreator<my::EnemyIdleComponent>();
    my::ComponentFactory::AddComponentCreator<my::EnemyMoveComponent>();
    my::ComponentFactory::AddComponentCreator<my::EnemyAttackComponent>();
    my::ComponentFactory::AddComponentCreator<my::MotionStateComponent>();
    my::ComponentFactory::AddComponentCreator<my::VelocityComponent>();
    my::ComponentFactory::AddComponentCreator<my::TransformComponent>();
    my::ComponentFactory::AddComponentCreator<my::MeshComponent>();
    my::ComponentFactory::AddComponentCreator<my::PlayerCollisionObject>();
    my::ComponentFactory::AddComponentCreator<my::EnemyCollisionObject>();
    my::ComponentFactory::AddComponentCreator<my::EnemySightCollisionObject>();

}

my::ComponentFactory::~ComponentFactory() {
}


void my::ComponentFactory::Release(void) {
    for (auto& factory : _component_creators) {
        factory.second->Release();
        factory.second.reset();
    } // for
    _component_creators.clear();
}

std::shared_ptr<my::Component> my::ComponentFactory::Create(const std::string& key, const rapidjson::Value& param) const {
    auto it = _component_creators.find(key);
    if (it != _component_creators.end()) {
        return it->second->Create(param);
    } // if
    return nullptr;
}