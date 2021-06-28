#include "FactoryManager.h"


ratchet::factory::FactoryManager::FactoryManager() :
    _component(),
    _builder(&_component),
    _actor(&_builder),
    _behaviour_node(),
    _behaviour_executor(&_behaviour_node),
    _resource(),
    _game() {
}

ratchet::factory::FactoryManager::~FactoryManager() {
}

ratchet::factory::FactoryManager& ratchet::factory::FactoryManager::Singleton(void) {
    static ratchet::factory::FactoryManager object;
    return object;
}

void ratchet::factory::FactoryManager::SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr) {
    this->_resource = ptr;
    _builder.SetResourceManager(_resource);
}

void ratchet::factory::FactoryManager::SetGameManager(std::weak_ptr<ratchet::game::GameManager> ptr) {
    this->_game = ptr;
    _actor.SetGameManager(_game);
}

std::shared_ptr<ratchet::component::Component> ratchet::factory::FactoryManager::CreateComponent(const char* name, const rapidjson::Value& param) const {
    return _component.Create(name, param);
}

std::shared_ptr<ratchet::factory::builder::IBuilder> ratchet::factory::FactoryManager::CreateBuilder(const char* path) const {
    return _builder.Create(path);
}

std::shared_ptr<ratchet::actor::Actor> ratchet::factory::FactoryManager::CreateActor(const char* path, ratchet::actor::Actor::Param* param) {
    return _actor.Create<ratchet::actor::Actor>(path, param);
}

std::shared_ptr<ratchet::actor::weapon::Mechanical> ratchet::factory::FactoryManager::CreateMechanicalWeapon(const char* type, const std::string& builder_key, ratchet::actor::Actor::Param* param) {
    return _actor.CreateMechanicalWeapon(type, builder_key, param);
}

ratchet::behaviour::NodeExecutorPtr ratchet::factory::FactoryManager::CreateBehaviourExecutor(const char* key) {
    return _behaviour_executor.Create(key);
}