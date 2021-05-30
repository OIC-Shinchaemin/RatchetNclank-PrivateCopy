#ifndef BEHAVIOUR_RANGED_ATTACK_NODE_H
#define BEHAVIOUR_RANGED_ATTACK_NODE_H


#include "../ActionNode.h"

#include "../../Executor/Action/RangedAttackNodeExecutor.h"


namespace behaviour {
class RangedAttackNode : public behaviour::ActionNodeBase {
    using super = behaviour::ActionNodeBase;
    using Executor = behaviour::RangedAttackNodeExecutor;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    RangedAttackNode() :
        super("RangedAttackNode") {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~RangedAttackNode() = default;
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual behaviour::NodeExecutorPtr CreateExecutor(void) const {
        auto ptr = std::const_pointer_cast<behaviour::Node>(super::shared_from_this());
        return std::make_shared<Executor>(ptr);
    }
    /// <summary>
    /// ノードの実行
    /// </summary>
    /// <param name="node_args">実行引数</param>
    /// <returns>true:実行の成功</returns>
    /// <returns>false:実行の失敗</returns>
    virtual bool Execute(std::any node_args) override {
        auto args = std::any_cast<Executor::NodeArgs>(node_args);

        _ASSERT_EXPR(!args.actor.expired(), L"無効なポインタを保持しています");
        _ASSERT_EXPR(!args.ai_com.expired(), L"無効なポインタを保持しています");
        _ASSERT_EXPR(!args.attack_com.expired(), L"無効なポインタを保持しています");
        _ASSERT_EXPR(!args.enemy_com.expired(), L"無効なポインタを保持しています");
        _ASSERT_EXPR(!args.motion_com.expired(), L"無効なポインタを保持しています");
        _ASSERT_EXPR(!args.state_com.expired(), L"無効なポインタを保持しています");

        if (args.state_com.lock()->IsEqual(state::EnemyActionStateType::kEnemyActionRangedAttackState) &&
            args.motion_com.lock()->IsEndMotion()) {
            args.ai_com.lock()->ChangeState("AICombatState");
            return false;
        } // if
        if (args.state_com.lock()->CanTransition(state::EnemyActionStateType::kEnemyActionRangedAttackState)) {
            args.state_com.lock()->ChangeState(state::EnemyActionStateType::kEnemyActionRangedAttackState);
            return false;
        } // if
        return false;
        /*
        auto args = std::any_cast<behaviour::RangedAttackNodeExecutor::NodeArgs>(node_args);
        args.ai_com.lock()->ChangeState("AICombatState");
        if (args.state_com.lock()->CanTransition(state::EnemyActionStateType::kEnemyActionRangedAttackState)) {
            args.state_com.lock()->ChangeState(state::EnemyActionStateType::kEnemyActionRangedAttackState);
        } // if
        return false;
        */
    }
};
}
#endif // !BEHAVIOUR_RANGED_ATTACK_NODE_H