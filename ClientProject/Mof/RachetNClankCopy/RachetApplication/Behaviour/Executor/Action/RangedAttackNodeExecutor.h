#ifndef BEHAVIOUR_RANGED_ATTACK_NODE_EXECUTOR_H
#define BEHAVIOUR_RANGED_ATTACK_NODE_EXECUTOR_H


#include "../ActionNodeExecutor.h"

#include <memory>

#include "../../../Component/AIStateComponent.h"
#include "../../../Component/MotionComponent.h"
#include "../../../Component/Enemy/EnemyComponent.h"
#include "../../../Component/Enemy/EnemyStateComponent.h"
#include "../../../Component/Enemy/EnemyRangedAttackComponent.h"


namespace behaviour {
class RangedAttackNodeExecutor : public behaviour::ActionNodeExecutor {
    using super = behaviour::ActionNodeExecutor;
public:
    struct NodeArgs {
        //! アクター
        std::weak_ptr<my::Actor> actor;
        //! AI
        std::weak_ptr<my::AIStateComponent> ai_com;
        //! モーション
        std::weak_ptr<my::MotionComponent> motion_com;
        //! エネミー
        std::weak_ptr<my::EnemyComponent> enemy_com;
        //! エネミー状態
        std::weak_ptr<my::EnemyStateComponent> state_com;
        //! 攻撃
        std::weak_ptr<my::EnemyRangedAttackComponent> attack_com;
    };
private:
    //! 実行引数
    behaviour::RangedAttackNodeExecutor::NodeArgs _node_args;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="node"></param>
    RangedAttackNodeExecutor(const behaviour::NodePtr& node) :
        super(node),
        _node_args() {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~RangedAttackNodeExecutor() = default;
    /// <summary>
    /// 実行時必要なポインタをキャッシュ
    /// </summary>
    /// <param actor=""></param>
    virtual void Prepare(std::any actor) override {
        super::Prepare(actor);
        _node_args.actor = super::_actor;
        if (auto actor = super::_actor.lock()) {
            _node_args.ai_com = actor->GetComponent<my::AIStateComponent>();
            _node_args.enemy_com = actor->GetComponent<my::EnemyComponent>();
            _node_args.motion_com = actor->GetComponent<my::MotionComponent>();
            _node_args.state_com = actor->GetComponent<my::EnemyStateComponent>();
            _node_args.attack_com = actor->GetComponent<my::ActionComponent>()->GetComponent<my::EnemyRangedAttackComponent>();
        } // if
    }
    /// <summary>
    /// ノードの実行
    /// </summary>
    /// <param name="actor">実行アクター</param>
    /// <returns>true:実行の成功</returns>
    /// <returns>false:実行の失敗</returns>
    virtual behaviour::INodeExecutor::Result Execute(void) override {
        return super::ActionNodeExecute(_node_args);
    }
};
}
#endif // !BEHAVIOUR_RANGED_ATTACK_NODE_EXECUTOR_H