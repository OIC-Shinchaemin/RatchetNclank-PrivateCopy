#ifndef BEHAVIOUR_NODE_EXECUTOR_H
#define BEHAVIOUR_NODE_EXECUTOR_H


#include "INodeExecutor.h"

#include "../Node/Node.h"

#include <Mof.h>


namespace behaviour {
template<typename Actor>
class NodeExecutor : public INodeExecutor<Actor> {
    using super = INodeExecutor<Actor>;
protected:
    //! 状態
    super::State _state;
    //! 対応ノード
    NodePtr<Actor> _node;
    //! 親
    NodeExecutorWeakPtr<Actor> _parent;
    //! 子供
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
    /// 実行時必要なポインタをキャッシュ
    /// </summary>
    /// <param actor=""></param>
    virtual void Prepare(Actor actor) override {
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
    /// <summary>
    /// デバッグ
    /// </summary>
    /// <typeparam name="Actor"></typeparam>
    virtual void DebugRender(Mof::CVector2 position) override {
        MofU32 color = MOF_COLOR_WHITE;
        if (_state == super::State::Inactive) {
            color = MOF_COLOR_WHITE;
        } // else if
        if (_state == super::State::Running) {
            color = MOF_COLOR_RED;
        } // if
        if (_state == super::State::Completed) {
            color = MOF_COLOR_GREEN;
        } // else if
        if (_state == super::State::Incompleted) {
            color = MOF_COLOR_BLUE;
        } // else if

        Mof::CFont font;
        font.Create(8, "");
        ::CGraphicsUtilities::RenderString(position.x, position.y, color, _node->GetName().c_str());
        font.Release();
        auto pos = position;
        pos.x += 200.0f;
        for (auto ptr : _children) {
            ptr->DebugRender(pos);
            pos.y += 20.0f;
        } // for
    }
    virtual void DebugRender(void) override {
        this->DebugRender(Mof::CVector2(10.0f, 10.0f));
    }
};
}
#endif // !BEHAVIOUR_NODE_EXECUTOR_H