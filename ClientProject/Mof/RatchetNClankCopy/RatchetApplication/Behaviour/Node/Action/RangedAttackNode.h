#ifndef RATCHET_BEHAVIOUR_RANGED_ATTACK_NODE_H
#define RATCHET_BEHAVIOUR_RANGED_ATTACK_NODE_H


#include "../ActionNode.h"

#include "../../Executor/Action/RangedAttackNodeExecutor.h"


namespace ratchet {  namespace behaviour {
class RangedAttackNode : public ratchet::behaviour::ActionNodeBase {
    using super = ratchet::behaviour::ActionNodeBase;
    using Executor = ratchet::behaviour::RangedAttackNodeExecutor;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    RangedAttackNode() :
        super("RangedAttackNode") {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~RangedAttackNode() = default;
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual ratchet::behaviour::NodeExecutorPtr CreateExecutor(void) const {
        auto ptr = std::const_pointer_cast<ratchet::behaviour::Node>(super::shared_from_this());
        return std::make_shared<Executor>(ptr);
    }
    /// <summary>
    /// �m�[�h�̎��s
    /// </summary>
    /// <param name="node_args">���s����</param>
    /// <returns>true:���s�̐���</returns>
    /// <returns>false:���s�̎��s</returns>
    virtual bool Execute(std::any node_args) override {
        auto args = std::any_cast<Executor::NodeArgs>(node_args);

        _ASSERT_EXPR(!args.actor.expired(), L"�����ȃ|�C���^��ێ����Ă��܂�");
        _ASSERT_EXPR(!args.ai_com.expired(), L"�����ȃ|�C���^��ێ����Ă��܂�");
        _ASSERT_EXPR(!args.attack_com.expired(), L"�����ȃ|�C���^��ێ����Ă��܂�");
        _ASSERT_EXPR(!args.ENEMY_com.expired(), L"�����ȃ|�C���^��ێ����Ă��܂�");
        _ASSERT_EXPR(!args.motion_com.expired(), L"�����ȃ|�C���^��ێ����Ă��܂�");
        _ASSERT_EXPR(!args.state_com.expired(), L"�����ȃ|�C���^��ێ����Ă��܂�");

        if (args.state_com.lock()->IsEqual(ratchet::state::EnemyActionStateType::kEnemyActionRangedAttackState) &&
            args.motion_com.lock()->IsEndMotion()) {
            args.ai_com.lock()->ChangeState("AICombatState");
            return false;
        } // if
        if (args.state_com.lock()->CanTransition(ratchet::state::EnemyActionStateType::kEnemyActionRangedAttackState)) {
            args.state_com.lock()->ChangeState(ratchet::state::EnemyActionStateType::kEnemyActionRangedAttackState);
            return false;
        } // if
        return false;
    }
};
}
}
#endif // !RATCHET_BEHAVIOUR_RANGED_ATTACK_NODE_H