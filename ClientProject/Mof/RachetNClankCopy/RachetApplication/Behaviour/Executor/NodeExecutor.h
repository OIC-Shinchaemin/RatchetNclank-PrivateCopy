#ifndef BEHAVIOUR_NODE_EXECUTOR_H
#define BEHAVIOUR_NODE_EXECUTOR_H


#include "INodeExecutor.h"

#include "../Node/Node.h"


namespace behaviour {
template<typename Actor>
class NodeExecutor : public INodeExecutor<Actor> {
    using super = INodeExecutor<Actor>;
protected:
    //! 状態
    super::State _state;
    //! 対応ノード
    NodePtr<Actor> _node;
    //! 親ノード
    NodeExecutorWeakPtr<Actor> _parent;
    //! 子ノード
    NodeExecutorList<Actor> _children;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="node"></param>
    NodeExecutor(const NodePtr<Actor>& node) :
        super(),
        _state(super::State::Inactive),
        _node(node),
        _parent(),
        _children() {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~NodeExecutor() = default;
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetParent(NodeExecutorWeakPtr<Actor> ptr) override {
        _parent = ptr;
    }
    /// <summary>
    /// ノードの実行処理
    /// </summary>
    /// <param name="actor">実行アクター</param>
    /// <returns>Succeeded:実行の成功</returns>
    /// <returns>Failed:実行の失敗</returns>
    virtual behaviour::INodeExecutor<Actor>::Result Execute(Actor& actor) override { return behaviour::INodeExecutor<Actor>::Result::Failure; }
    /// <summary>
    /// 実行状態を全てリセット
    /// 状態をInactiveに設定
    /// </summary>
    /// <param name=""></param>
    virtual void Reset(void) override {
        _state = super::State::Inactive;
    }
};
}
#endif // !BEHAVIOUR_NODE_EXECUTOR_H