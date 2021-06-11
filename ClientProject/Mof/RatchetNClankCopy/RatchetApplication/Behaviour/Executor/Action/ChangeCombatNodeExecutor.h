#ifndef RATCHET_BEHAVIOUR_CHANGE_COMBAT_NODE_EXECUTOR_H
#define RATCHET_BEHAVIOUR_CHANGE_COMBAT_NODE_EXECUTOR_H


#include "../ActionNodeExecutor.h"

#include <memory>

#include "../../../Component/AIStateComponent.h"


namespace ratchet {
namespace behaviour {
class ChangeCombatNodeExecutor : public ratchet::behaviour::ActionNodeExecutor {
    using super = ratchet::behaviour::ActionNodeExecutor;
public:
    struct NodeArgs {
        //! アクター
        std::weak_ptr<ratchet::Actor> actor;
        //! AI
        std::weak_ptr<ratchet::AIStateComponent> ai_com;
    };
private:
    //! 実行引数
    ratchet::behaviour::ChangeCombatNodeExecutor::NodeArgs _node_args;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="node"></param>
    ChangeCombatNodeExecutor(const ratchet::behaviour::NodePtr& node) :
        super(node),
        _node_args() {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~ChangeCombatNodeExecutor() = default;
    /// <summary>
    /// 実行時必要なポインタをキャッシュ
    /// </summary>
    /// <param actor=""></param>
    virtual void Prepare(std::any actor) override {
        super::Prepare(actor);
        _node_args.actor = super::_actor;
        if (auto actor = super::_actor.lock()) {
            _node_args.ai_com = actor->GetComponent<ratchet::AIStateComponent>();
        } // if
    }
    /// <summary>
    /// ノードの実行
    /// </summary>
    /// <param name="actor">実行アクター</param>
    /// <returns>true:実行の成功</returns>
    /// <returns>false:実行の失敗</returns>
    virtual ratchet::behaviour::INodeExecutor::Result Execute(void) override {
        return super::ActionNodeExecute(_node_args);
    }
};
}
}
#endif // !RATCHET_BEHAVIOUR_CHANGE_COMBAT_NODE_EXECUTOR_H