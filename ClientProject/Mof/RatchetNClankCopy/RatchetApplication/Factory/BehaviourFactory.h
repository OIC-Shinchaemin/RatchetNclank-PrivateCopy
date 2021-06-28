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
    //! �R���|�W�b�g
    ratchet::factory::Factory<behaviour::CompositeNode> _composite_factory;
    //! �A�N�V����
    ratchet::factory::Factory<behaviour::ActionNodeBase> _action_factory;
    //! �R���f�B�V����
    ratchet::factory::Factory<behaviour::ConditionalNodeBase> _condition_factory;
    //! �f�R���[�^�[
    ratchet::factory::Factory<behaviour::DecoratorNodeBase> _decorator_factory;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    BehaviourFactory();
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name="path"></param>
    /// <returns></returns>
    behaviour::CompositeNodePtr CreateRootNode(const char* path);
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name="behaviours"></param>
    /// <param name="index"></param>
    /// <returns></returns>
    std::shared_ptr<behaviour::CompositeNode> CreateCompositeNode(rapidjson::Value& behaviours, uint32_t index);
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name="behaviours"></param>
    /// <param name="index"></param>
    /// <returns></returns>
    std::shared_ptr<behaviour::ActionNodeBase> CreateActionNode(rapidjson::Value& behaviours, uint32_t index);
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name="behaviours"></param>
    /// <param name="index"></param>
    /// <returns></returns>
    std::shared_ptr<behaviour::ConditionalNodeBase> CreateConditionalNode(rapidjson::Value& behaviours, uint32_t index);
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name="behaviours"></param>
    /// <param name="index"></param>
    /// <returns></returns>
    std::shared_ptr<behaviour::DecoratorNodeBase> CreateDecoratorNode(rapidjson::Value& behaviours, uint32_t index);
};
}
}
#endif // !RATCHET_FACTORY_BEHAVIOUR_FACTORY_H