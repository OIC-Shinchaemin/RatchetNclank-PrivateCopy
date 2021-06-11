#ifndef RACHET_BEHAVIOUR_EXECUTOR_FACTORY_H
#define RACHET_BEHAVIOUR_EXECUTOR_FACTORY_H


#include <memory>
#include <string>
#include <unordered_map>

#include "../Behaviour/Executor/INodeExecutor.h"
#include "BehaviourFactory.h"


namespace rachet {
class BehaviourExecutorFactory {
    //! マップ
    std::unordered_map<std::string, behaviour::CompositeNodePtr > _behaviour_map;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="behaviour_factory"></param>
    BehaviourExecutorFactory(rachet::BehaviourFactory* behaviour_factory);
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    behaviour::NodeExecutorPtr Create(const char* key) const;
};
}
#endif // !RACHET_BEHAVIOUR_EXECUTOR_FACTORY_H