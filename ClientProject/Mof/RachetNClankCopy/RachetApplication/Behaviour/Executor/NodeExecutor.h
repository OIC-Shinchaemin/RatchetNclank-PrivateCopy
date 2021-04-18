#ifndef BEHAVIOUR_NODE_EXECUTOR_H
#define BEHAVIOUR_NODE_EXECUTOR_H


#include "INodeExecutor.h"

#include <Mof.h>

#include "../Node/Node.h"


namespace behaviour {
class NodeExecutor : public behaviour::INodeExecutor {
    using super = behaviour::INodeExecutor;
protected:
    //! 状態
    super::State _state;
    //! 対応ノード
    behaviour::NodePtr _node;
    //! 親
    behaviour::NodeExecutorWeakPtr _parent;
    //! 子供
    behaviour::NodeExecutorList _children;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="node"></param>
    NodeExecutor(const behaviour::NodePtr& node) :
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
    void SetParent(behaviour::NodeExecutorWeakPtr ptr) override {
        _parent = ptr;
    }
    /// <summary>
    /// 実行時必要なポインタをキャッシュ
    /// </summary>
    /// <param actor=""></param>
    virtual void Prepare(std::any actor) override {
    }
    /// <summary>
    /// ノードの実行処理
    /// </summary>
    /// <param name="actor">実行アクター</param>
    /// <returns>Succeeded:実行の成功</returns>
    /// <returns>Failed:実行の失敗</returns>
    virtual behaviour::INodeExecutor::Result Execute(void) override {
        return behaviour::INodeExecutor::Result::Failure;
    }
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
        //this->DebugRender(Mof::CVector2(10.0f, 10.0f));
    }
};
}
#endif // !BEHAVIOUR_NODE_EXECUTOR_H