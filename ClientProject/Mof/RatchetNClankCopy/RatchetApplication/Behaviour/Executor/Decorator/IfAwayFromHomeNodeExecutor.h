#ifndef RATCHET_BEHAVIOUR_IF_AWAY_FROM_HOME_NODE_EXECUTOR_H
#define RATCHET_BEHAVIOUR_IF_AWAY_FROM_HOME_NODE_EXECUTOR_H


#include "../DecoratorNodeExecutor.h"

#include "../../../Component/Enemy/EnemyComponent.h"


namespace ratchet {
namespace behaviour {
class IfAwayFromHomeNodeExecutor : public ratchet::behaviour::DecoratorNodeExecutor {
    using super = ratchet::behaviour::DecoratorNodeExecutor;
public:
    struct NodeArgs {
        //! アクター
        std::weak_ptr<ratchet::actor::Actor> actor;
        //! 型
        std::weak_ptr<ratchet::component::enemy::EnemyComponent> type_com;
    };
private:
    //! 実行引数
    ratchet::behaviour::IfAwayFromHomeNodeExecutor::NodeArgs _node_args;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="node"></param>
    IfAwayFromHomeNodeExecutor(const ratchet::behaviour::SimplexNodePtr& node) :
        super(node),
        _node_args() {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~IfAwayFromHomeNodeExecutor() = default;
    /// <summary>
    /// 実行時必要なポインタをキャッシュ
    /// </summary>
    /// <param actor=""></param>
    virtual void Prepare(std::any actor) override {
        super::Prepare(actor);
        _node_args.actor = super::_actor;
        if (auto actor = super::_actor.lock()) {
            _node_args.type_com = actor->GetComponent<ratchet::component::enemy::EnemyComponent>();
        } // if
    }
    /// <summary>
    /// ノードの実行
    /// </summary>
    /// <param name="actor">実行アクター</param>
    /// <returns>true:実行の成功</returns>
    /// <returns>false:実行の失敗</returns>
    virtual ratchet::behaviour::INodeExecutor::Result Execute(void) override {
        return super::DecoratorNodeExecute(_node_args);
    }
};
}
}
#endif // !RATCHET_BEHAVIOUR_IF_AWAY_FROM_HOME_NODE_EXECUTOR_H