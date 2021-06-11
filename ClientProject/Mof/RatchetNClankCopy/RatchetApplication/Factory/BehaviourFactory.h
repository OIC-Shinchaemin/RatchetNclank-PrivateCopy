#ifndef RATCHET_FACTORY_BEHAVIOUR_FACTORY_H
#define RATCHET_FACTORY_BEHAVIOUR_FACTORY_H


#include <memory>
#include <string>
#include <unordered_map>

#include "Factory.h"
#include "../Behaviour/Node/CompositeNode.h"
#include "../Behaviour/Node/ActionNode.h"
#include "../Behaviour/Node/ConditionalNode.h"
#include "../Behaviour/Node/DecoratorNode.h"


namespace ratchet {
namespace factory {
class BehaviourFactory {
private:
    //! コンポジット
    ratchet::factory::Factory<behaviour::CompositeNode> _composite_factory;
    //! アクション
    ratchet::factory::Factory<behaviour::ActionNodeBase> _action_factory;
    //! コンディション
    ratchet::factory::Factory<behaviour::ConditionalNodeBase> _condition_factory;
    //! デコレーター
    ratchet::factory::Factory<behaviour::DecoratorNodeBase> _decorator_factory;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    BehaviourFactory();
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="path"></param>
    /// <returns></returns>
    behaviour::CompositeNodePtr CreateRootNode(const char* path);
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="behaviours"></param>
    /// <param name="index"></param>
    /// <returns></returns>
    std::shared_ptr<behaviour::CompositeNode> CreateCompositeNode(rapidjson::Value& behaviours, uint32_t index);
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="behaviours"></param>
    /// <param name="index"></param>
    /// <returns></returns>
    std::shared_ptr<behaviour::ActionNodeBase> CreateActionNode(rapidjson::Value& behaviours, uint32_t index);
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="behaviours"></param>
    /// <param name="index"></param>
    /// <returns></returns>
    std::shared_ptr<behaviour::ConditionalNodeBase> CreateConditionalNode(rapidjson::Value& behaviours, uint32_t index);
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="behaviours"></param>
    /// <param name="index"></param>
    /// <returns></returns>
    std::shared_ptr<behaviour::DecoratorNodeBase> CreateDecoratorNode(rapidjson::Value& behaviours, uint32_t index);
};
}
}
#endif // !RATCHET_FACTORY_BEHAVIOUR_FACTORY_H