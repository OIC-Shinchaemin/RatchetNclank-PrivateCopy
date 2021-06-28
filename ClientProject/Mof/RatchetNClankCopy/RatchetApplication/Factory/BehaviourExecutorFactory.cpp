#include "BehaviourExecutorFactory.h"


ratchet::factory::BehaviourExecutorFactory::BehaviourExecutorFactory(ratchet::factory::BehaviourFactory* behaviour_factory) :
    _behaviour_map() {
    _behaviour_map.emplace("../Resource/behaviour/patrol.json",
                           behaviour_factory->CreateRootNode("../Resource/behaviour/patrol.json"));
    _behaviour_map.emplace("../Resource/behaviour/combat.json",
                           behaviour_factory->CreateRootNode("../Resource/behaviour/combat.json"));

    _behaviour_map.emplace("../Resource/behaviour/weak_enemy_patrol.json",
                           behaviour_factory->CreateRootNode("../Resource/behaviour/weak_enemy_patrol.json"));
    _behaviour_map.emplace("../Resource/behaviour/weak_enemy_combat.json",
                           behaviour_factory->CreateRootNode("../Resource/behaviour/weak_enemy_combat.json"));
    _behaviour_map.emplace("../Resource/behaviour/strong_enemy_patrol.json",
                           behaviour_factory->CreateRootNode("../Resource/behaviour/strong_enemy_patrol.json"));
    _behaviour_map.emplace("../Resource/behaviour/strong_enemy_combat.json",
                           behaviour_factory->CreateRootNode("../Resource/behaviour/strong_enemy_combat.json"));

}

ratchet::behaviour::NodeExecutorPtr ratchet::factory::BehaviourExecutorFactory::Create(const char* key) const {
    auto it = _behaviour_map.find(key);
    if (it != _behaviour_map.end()) {
        return it->second->CreateExecutor();
    } // if
    return nullptr;
}