#include "BehaviourExecutorFactory.h"


my::BehaviourExecutorFactory::BehaviourExecutorFactory(my::BehaviourFactory* behaviour_factory) :
    _behaviour_map() {
    _behaviour_map.emplace("../Resource/behaviour/patrol.json", behaviour_factory->CreateRootNode("../Resource/behaviour/patrol.json"));
    _behaviour_map.emplace("../Resource/behaviour/combat.json", behaviour_factory->CreateRootNode("../Resource/behaviour/combat.json"));
}

behaviour::NodeExecutorPtr my::BehaviourExecutorFactory::Create(const char* key) const {
    auto it = _behaviour_map.find(key);
    if (it != _behaviour_map.end()) {
        return it->second->CreateExecutor();
    } // if
    return nullptr;
}