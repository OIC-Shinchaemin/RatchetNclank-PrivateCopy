#ifndef MY_BEHAVIOUR_FACTORY_H
#define MY_BEHAVIOUR_FACTORY_H


#include <memory>
#include <string>
#include <unordered_map>

#include "Factory.h"
#include "../Behaviour/Node/CompositeNode.h"
#include "../Behaviour/Node/ActionNode.h"
#include "../Behaviour/Node/ConditionalNode.h"
#include "../Behaviour/Node/DecoratorNode.h"


namespace my {
class BehaviourFactory {
private:
    //! コンポジット
    my::Factory<behaviour::CompositeNode> _composite_factory;
    //! アクション
    my::Factory<behaviour::ActionNodeBase> _action_factory;
    //! コンディション
    my::Factory<behaviour::ConditionalNodeBase> _condition_factory;
    //! デコレーター
    my::Factory<behaviour::DecoratorNodeBase> _decorator_factory;
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
#endif // !MY_BEHAVIOUR_FACTORY_H