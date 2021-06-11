#ifndef BEHAVIOUR_LOOK_AROUND_NODE_EXECUTOR_H
#define BEHAVIOUR_LOOK_AROUND_NODE_EXECUTOR_H


#include "../ActionNodeExecutor.h"

#include <memory>

#include "../../../Component/AIStateComponent.h"
#include "../../../Component/Enemy/EnemyComponent.h"
#include "../../../Component/Enemy/EnemyStateComponent.h"


namespace behaviour {
class LookAroundNodeExecutor : public behaviour::ActionNodeExecutor {
    using super = behaviour::ActionNodeExecutor;
public:
    struct NodeArgs {
        //! アクター
        std::weak_ptr<ratchet::Actor> actor;
        //! AI
        std::weak_ptr<ratchet::AIStateComponent> ai_com;
        //! エネミー
        std::weak_ptr<ratchet::EnemyComponent> ENEMY_com;
        //! エネミー状態
        std::weak_ptr<ratchet::EnemyStateComponent> state_com;
    };
private:
    //! 実行引数
    behaviour::LookAroundNodeExecutor::NodeArgs _node_args;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="node"></param>
    LookAroundNodeExecutor(const behaviour::NodePtr& node) :
        super(node),
        _node_args() {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~LookAroundNodeExecutor() = default;
    /// <summary>
    /// 実行時必要なポインタをキャッシュ
    /// </summary>
    /// <param actor=""></param>
    virtual void Prepare(std::any actor) override {
        super::Prepare(actor);
        _node_args.actor = super::_actor;
        if (auto actor = super::_actor.lock()) {
            _node_args.ai_com = actor->GetComponent<ratchet::AIStateComponent>();
            _node_args.ENEMY_com = actor->GetComponent<ratchet::EnemyComponent>();
            _node_args.state_com = actor->GetComponent<ratchet::EnemyStateComponent>();
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
#endif // !BEHAVIOUR_LOOK_AROUND_NODE_EXECUTOR_H