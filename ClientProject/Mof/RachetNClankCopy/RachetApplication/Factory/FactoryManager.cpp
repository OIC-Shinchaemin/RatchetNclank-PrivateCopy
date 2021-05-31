#include "FactoryManager.h"


my::FactoryManager::FactoryManager() :
    _component(),
    _builder(&_component),
    _actor(&_builder),
    _behaviour_node(),
    _behaviour_executor(&_behaviour_node),
    _resource(),
    _game() {
}

my::FactoryManager::~FactoryManager() {
}

my::FactoryManager& my::FactoryManager::Singleton(void) {
    static my::FactoryManager object;
    return object;
}

void my::FactoryManager::SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr) {
    this->_resource = ptr;
    _builder.SetResourceManager(_resource);
}

void my::FactoryManager::SetGameManager(std::weak_ptr<my::GameManager> ptr) {
    this->_game = ptr;
    _actor.SetGameManager(_game);
}

std::shared_ptr<my::Component> my::FactoryManager::CreateComponent(const char* name, const rapidjson::Value& param) const {
    return _component.Create(name, param);
}

std::shared_ptr<my::IBuilder> my::FactoryManager::CreateBuilder(const char* path) const {
    return _builder.Create(path);
}

std::shared_ptr<my::Actor> my::FactoryManager::CreateActor(const char* path, my::Actor::Param* param) {
    return _actor.Create<my::Actor>(path, param);
}

std::shared_ptr<my::Mechanical> my::FactoryManager::CreateMechanicalWeapon(const char* type, const std::string& builder_key, my::Actor::Param* param) {
    return _actor.CreateMechanicalWeapon(type, builder_key, param);
}

behaviour::NodeExecutorPtr my::FactoryManager::CreateBehaviourExecutor(const char* key) {
    return _behaviour_executor.Create(key);
}