#include "FactoryManager.h"


rachet::FactoryManager::FactoryManager() :
    _component(),
    _builder(&_component),
    _actor(&_builder),
    _behaviour_node(),
    _behaviour_executor(&_behaviour_node),
    _resource(),
    _game() {
}

rachet::FactoryManager::~FactoryManager() {
}

rachet::FactoryManager& rachet::FactoryManager::Singleton(void) {
    static rachet::FactoryManager object;
    return object;
}

void rachet::FactoryManager::SetResourceManager(std::weak_ptr<rachet::ResourceMgr> ptr) {
    this->_resource = ptr;
    _builder.SetResourceManager(_resource);
}

void rachet::FactoryManager::SetGameManager(std::weak_ptr<rachet::GameManager> ptr) {
    this->_game = ptr;
    _actor.SetGameManager(_game);
}

std::shared_ptr<rachet::Component> rachet::FactoryManager::CreateComponent(const char* name, const rapidjson::Value& param) const {
    return _component.Create(name, param);
}

std::shared_ptr<rachet::IBuilder> rachet::FactoryManager::CreateBuilder(const char* path) const {
    return _builder.Create(path);
}

std::shared_ptr<rachet::Actor> rachet::FactoryManager::CreateActor(const char* path, rachet::Actor::Param* param) {
    return _actor.Create<rachet::Actor>(path, param);
}

std::shared_ptr<rachet::Mechanical> rachet::FactoryManager::CreateMechanicalWeapon(const char* type, const std::string& builder_key, rachet::Actor::Param* param) {
    return _actor.CreateMechanicalWeapon(type, builder_key, param);
}

behaviour::NodeExecutorPtr rachet::FactoryManager::CreateBehaviourExecutor(const char* key) {
    return _behaviour_executor.Create(key);
}