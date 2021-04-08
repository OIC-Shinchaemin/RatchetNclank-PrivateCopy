#include "FactoryManager.h"


my::FactoryManager::FactoryManager() :
    _behaviour_node(),
    _behaviour_executor(&_behaviour_node) {
}

my::FactoryManager::~FactoryManager() {
}

my::FactoryManager& my::FactoryManager::Singleton(void) {
    static my::FactoryManager object;
    return object;
}

behaviour::NodeExecutorPtr<std::shared_ptr<my::Enemy>> my::FactoryManager::CreateBehaviourExecutor(const char* key) {
    return _behaviour_executor.Create(key);
}