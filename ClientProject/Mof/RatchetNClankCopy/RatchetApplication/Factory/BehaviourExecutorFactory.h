#ifndef RATCHET_FACTORY_BEHAVIOUR_EXECUTOR_FACTORY_H
#define RATCHET_FACTORY_BEHAVIOUR_EXECUTOR_FACTORY_H


#include <memory>
#include <string>
#include <unordered_map>

#include "../Behaviour/Executor/INodeExecutor.h"
#include "BehaviourFactory.h"


namespace ratchet {
namespace factory {
class BehaviourExecutorFactory {
    //! マップ
    std::unordered_map<std::string, behaviour::CompositeNodePtr > _behaviour_map;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="behaviour_factory"></param>
    BehaviourExecutorFactory(ratchet::factory::BehaviourFactory* behaviour_factory);
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    behaviour::NodeExecutorPtr Create(const char* key) const;
};
}
}
#endif // !RATCHET_FACTORY_BEHAVIOUR_EXECUTOR_FACTORY_H