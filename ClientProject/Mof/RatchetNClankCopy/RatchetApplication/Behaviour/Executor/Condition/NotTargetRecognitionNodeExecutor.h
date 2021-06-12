#ifndef RATCHET_BEHAVIOUR_NOT_TARGET_RECOGNITION_NODE_EXECUTOR_H
#define RATCHET_BEHAVIOUR_NOT_TARGET_RECOGNITION_NODE_EXECUTOR_H


#include "../ConditionalNodeExecutor.h"

#include "../../../Component/Enemy/EnemyComponent.h"


namespace ratchet {
namespace behaviour {
class NotTargetRecognitionNodeExecutor : public ratchet::behaviour::ConditionalNodeExecutor {
    using super = ratchet::behaviour::ConditionalNodeExecutor;
public:
    struct NodeArgs {
        //! アクター
        std::weak_ptr<ratchet::actor::Actor> actor;
        //! エネミー
        std::weak_ptr<ratchet::component::enemy::EnemyComponent> ENEMY_com;
    };
private:
    //! 実行引数
    ratchet::behaviour::NotTargetRecognitionNodeExecutor::NodeArgs _node_args;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="node"></param>
    NotTargetRecognitionNodeExecutor(const ratchet::behaviour::NodePtr& node) :
        super(node),
        _node_args() {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~NotTargetRecognitionNodeExecutor() = default;
    /// <summary>
    /// 実行時必要なポインタをキャッシュ
    /// </summary>
    /// <param actor=""></param>
    virtual void Prepare(std::any actor) override {
        super::Prepare(actor);
        _node_args.actor = super::_actor;
        if (auto actor = super::_actor.lock()) {
            _node_args.ENEMY_com = actor->GetComponent<ratchet::component::enemy::EnemyComponent>();
        } // if
    }
    /// <summary>
    /// ノードの実行
    /// </summary>
    /// <param name="actor">実行アクター</param>
    /// <returns>true:実行の成功</returns>
    /// <returns>false:実行の失敗</returns>
    virtual ratchet::behaviour::INodeExecutor::Result Execute(void) override {
        return super::ConditionalNodeExecute(_node_args);
    }
};
}
}
#endif // !RATCHET_BEHAVIOUR_NOT_TARGET_RECOGNITION_NODE_EXECUTOR_H