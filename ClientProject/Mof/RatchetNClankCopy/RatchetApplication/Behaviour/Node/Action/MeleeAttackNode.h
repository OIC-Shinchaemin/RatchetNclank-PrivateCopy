#ifndef RATCHET_BEHAVIOUR_MELLE_ATTACK_NODE_H
#define RATCHET_BEHAVIOUR_MELLE_ATTACK_NODE_H


#include "../ActionNode.h"

#include "../../Executor/Action/MeleeAttackNodeExecutor.h"


namespace ratchet {  namespace behaviour {
class MeleeAttackNode : public ratchet::behaviour::ActionNodeBase {
    using super = ratchet::behaviour::ActionNodeBase;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    MeleeAttackNode() :
        super("MeleeAttackNode") {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~MeleeAttackNode() = default;
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual ratchet::behaviour::NodeExecutorPtr CreateExecutor(void) const {
        auto ptr = std::const_pointer_cast<ratchet::behaviour::Node>(super::shared_from_this());
        return std::make_shared<ratchet::behaviour::MeleeAttackNodeExecutor>(ptr);
    }
    /// <summary>
    /// ノードの実行
    /// </summary>
    /// <param name="node_args">実行引数</param>
    /// <returns>true:実行の成功</returns>
    /// <returns>false:実行の失敗</returns>
    virtual bool Execute(std::any node_args) override {
        auto args = std::any_cast<ratchet::behaviour::MeleeAttackNodeExecutor::NodeArgs>(node_args);

        _ASSERT_EXPR(!args.actor.expired(), L"無効なポインタを保持しています");
        _ASSERT_EXPR(!args.ai_com.expired(), L"無効なポインタを保持しています");
        _ASSERT_EXPR(!args.attack_com.expired(), L"無効なポインタを保持しています");
        _ASSERT_EXPR(!args.ENEMY_com.expired(), L"無効なポインタを保持しています");
        _ASSERT_EXPR(!args.motion_com.expired(), L"無効なポインタを保持しています");
        _ASSERT_EXPR(!args.state_com.expired(), L"無効なポインタを保持しています");

        if (args.state_com.lock()->IsEqual(ratchet::state::EnemyActionStateType::kEnemyActionMeleeAttackState) &&
            args.motion_com.lock()->IsEndMotion()) {
            args.ai_com.lock()->ChangeState("AICombatState");
            return false;
        } // if
        if (args.state_com.lock()->CanTransition(ratchet::state::EnemyActionStateType::kEnemyActionMeleeAttackState)) {
            args.state_com.lock()->ChangeState(ratchet::state::EnemyActionStateType::kEnemyActionMeleeAttackState);
            return false;
        } // if
        return false;
    }
};
}
}
#endif // !RATCHET_BEHAVIOUR_MELLE_ATTACK_NODE_H