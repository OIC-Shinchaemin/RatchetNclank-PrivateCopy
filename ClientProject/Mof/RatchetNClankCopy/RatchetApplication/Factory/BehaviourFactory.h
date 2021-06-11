#ifndef RATCHET_BEHAVIOUR_FACTORY_H
#define RATCHET_BEHAVIOUR_FACTORY_H


#include <memory>
#include <string>
#include <unordered_map>

#include "Factory.h"
#include "../Behaviour/Node/CompositeNode.h"
#include "../Behaviour/Node/ActionNode.h"
#include "../Behaviour/Node/ConditionalNode.h"
#include "../Behaviour/Node/DecoratorNode.h"


namespace ratchet {
class BehaviourFactory {
private:
    //! コンポジット
    ratchet::Factory<behaviour::CompositeNode> _composite_factory;
    //! アクション
    ratchet::Factory<behaviour::ActionNodeBase> _action_factory;
    //! コンディション
    ratchet::Factory<behaviour::ConditionalNodeBase> _condition_factory;
    //! デコレーター
    ratchet::Factory<behaviour::DecoratorNodeBase> _decorator_factory;
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
#endif // !RATCHET_BEHAVIOUR_FACTORY_H