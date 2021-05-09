#ifndef MY_BEHAVIOUR_FACTORY_H
#define MY_BEHAVIOUR_FACTORY_H


#include <memory>
#include <string>
#include <unordered_map>

#include "../GameDefine.h"
#include "Factory.h"
#include "../Behaviour/Node/CompositeNode.h"
#include "../Behaviour/Node/ConditionalNode.h"
#include "../Behaviour/Node/DecoratorNode.h"
#include "../Behaviour/Node/ActionNode.h"
#include "../Behaviour/Node/SequencerNode.h"
#include "../Behaviour/Node/SelectorNode.h"
#include "../Actor/Character/Enemy.h"


namespace my {
class BehaviourFactory {
private:
    //! アクション
    my::Factory<behaviour::ActionNodeBase> _action_factory;
    //! アクション
    my::Factory<behaviour::ConditionalNodeBase> _condition_factory;
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
    /// ゲッター
    /// </summary>
    /// <param name="type"></param>
    /// <returns></returns>
    behaviour::ConditionalNodeBase::Operator GetConditionalOperator(std::string type);
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
    std::shared_ptr<behaviour::SequencerNode> CreateSequencerNode(rapidjson::Value& behaviours, uint32_t index);
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="behaviours"></param>
    /// <param name="index"></param>
    /// <returns></returns>
    std::shared_ptr<behaviour::SelectorNode> CreateSelectorNode(rapidjson::Value& behaviours, uint32_t index);
};
}
#endif // !MY_BEHAVIOUR_FACTORY_H