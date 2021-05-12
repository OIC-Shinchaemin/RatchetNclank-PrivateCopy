#ifndef BEHAVIOUR_NOT_TARGET_RECOGNITION_NODE_EXECUTOR_H
#define BEHAVIOUR_NOT_TARGET_RECOGNITION_NODE_EXECUTOR_H


#include "../ConditionalNodeExecutor.h"

#include "../../../Component/Enemy/EnemyComponent.h"


namespace behaviour {
class NotTargetRecognitionNodeExecutor : public behaviour::ConditionalNodeExecutor {
    using super = behaviour::ConditionalNodeExecutor;
public:
    struct NodeArgs {
        //! アクター
        std::weak_ptr<my::Actor> actor;
        //! エネミー
        std::weak_ptr<my::EnemyComponent> enemy_com;
    };
private:
    //! 実行引数
    behaviour::NotTargetRecognitionNodeExecutor::NodeArgs _node_args;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="node"></param>
    NotTargetRecognitionNodeExecutor(const behaviour::NodePtr& node) :
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
            _node_args.enemy_com = actor->GetComponent<my::EnemyComponent>();
        } // if
    }
    /// <summary>
    /// ノードの実行
    /// </summary>
    /// <param name="actor">実行アクター</param>
    /// <returns>true:実行の成功</returns>
    /// <returns>false:実行の失敗</returns>
    virtual behaviour::INodeExecutor::Result Execute(void) override {
        return super::ConditionalNodeExecute(_node_args);
    }
};
}
#endif // !BEHAVIOUR_NOT_TARGET_RECOGNITION_NODE_EXECUTOR_H