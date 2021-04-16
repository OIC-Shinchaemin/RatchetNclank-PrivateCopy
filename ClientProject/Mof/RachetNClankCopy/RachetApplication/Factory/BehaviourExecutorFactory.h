#ifndef MY_BEHAVIOUR_EXECUTOR_FACTORY_H
#define MY_BEHAVIOUR_EXECUTOR_FACTORY_H


#include <memory>
#include <string>
#include <unordered_map>

#include "../Behaviour/Executor/INodeExecutor.h"
#include "BehaviourFactory.h"


namespace my {
class BehaviourExecutorFactory {
    //! マップ
    std::unordered_map<std::string, behaviour::CompositeNodePtr > _behaviour_map;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="behaviour_factory"></param>
    BehaviourExecutorFactory(my::BehaviourFactory* behaviour_factory) :
        _behaviour_map() {
        //_behaviour_map.emplace("../Resource/behaviour/patrol.json", behaviour_factory->CreateRootNode("../Resource/behaviour/patrol.json"));
        _behaviour_map.emplace("../Resource/behaviour/combat.json", behaviour_factory->CreateRootNode("../Resource/behaviour/combat.json"));
        _behaviour_map.emplace("../Resource/behaviour/test.json", behaviour_factory->CreateRootNode("../Resource/behaviour/test.json"));
    }
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    behaviour::NodeExecutorPtr Create(const char* key) const {
        auto it = _behaviour_map.find(key);
        if (it != _behaviour_map.end()) {
            return it->second->CreateExecutor();
        } // if
        return nullptr;
    }
};
}
#endif // !MY_BEHAVIOUR_EXECUTOR_FACTORY_H