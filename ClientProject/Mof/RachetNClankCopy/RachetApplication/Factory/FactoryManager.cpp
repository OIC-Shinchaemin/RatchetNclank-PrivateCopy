#include "FactoryManager.h"


ratchet::FactoryManager::FactoryManager() :
    _component(),
    _builder(&_component),
    _actor(&_builder),
    _behaviour_node(),
    _behaviour_executor(&_behaviour_node),
    _resource(),
    _game() {
}

ratchet::FactoryManager::~FactoryManager() {
}

ratchet::FactoryManager& ratchet::FactoryManager::Singleton(void) {
    static ratchet::FactoryManager object;
    return object;
}

void ratchet::FactoryManager::SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr) {
    this->_resource = ptr;
    _builder.SetResourceManager(_resource);
}

void ratchet::FactoryManager::SetGameManager(std::weak_ptr<ratchet::GameManager> ptr) {
    this->_game = ptr;
    _actor.SetGameManager(_game);
}

std::shared_ptr<ratchet::Component> ratchet::FactoryManager::CreateComponent(const char* name, const rapidjson::Value& param) const {
    return _component.Create(name, param);
}

std::shared_ptr<ratchet::IBuilder> ratchet::FactoryManager::CreateBuilder(const char* path) const {
    return _builder.Create(path);
}

std::shared_ptr<ratchet::Actor> ratchet::FactoryManager::CreateActor(const char* path, ratchet::Actor::Param* param) {
    return _actor.Create<ratchet::Actor>(path, param);
}

std::shared_ptr<ratchet::Mechanical> ratchet::FactoryManager::CreateMechanicalWeapon(const char* type, const std::string& builder_key, ratchet::Actor::Param* param) {
    return _actor.CreateMechanicalWeapon(type, builder_key, param);
}

behaviour::NodeExecutorPtr ratchet::FactoryManager::CreateBehaviourExecutor(const char* key) {
    return _behaviour_executor.Create(key);
}