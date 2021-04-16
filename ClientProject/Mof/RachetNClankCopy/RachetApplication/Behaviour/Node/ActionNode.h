#ifndef BEHAVIOUR_ACTION_NODE_H
#define BEHAVIOUR_ACTION_NODE_H


#include "Node.h"

#include "../Executor/ActionNodeExecutor.h"


namespace behaviour {
template<typename Actor>
class ActionNodeBase : public behaviour::Node<Actor> {
    using super = behaviour::Node<Actor>;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ActionNodeBase(const std::string& name) :
        super(name) {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~ActionNodeBase() = default;
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual behaviour::NodeExecutorPtr<Actor> CreateExecutor(void) const {
        auto ptr = std::const_pointer_cast<super>(super::shared_from_this());
        return std::make_shared<ActionNodeExecutor<Actor>>(ptr);
    }
};
template<typename Actor>
class FunctionNode : public behaviour::ActionNodeBase<Actor> {
    using super = behaviour::ActionNodeBase<Actor>;
protected:
    //! 実行処理
    using OnExecFunction = std::function< bool(Actor&) >;
    //! 実行処理
    OnExecFunction OnExec;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="exec"></param>
    FunctionNode(OnExecFunction exec) :
        super("FunctionNode"), 
        OnExec(exec) {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~FunctionNode() = default;
    /// <summary>
    /// ノードの実行
    /// </summary>
    /// <param name="actor">実行アクター</param>
    /// <returns>true:実行の成功</returns>
    /// <returns>false:実行の失敗</returns>
    virtual bool Execute(std::any ptr) override{
        auto actor = std::any_cast<Actor>(ptr);
        return OnExec(actor);
    }
};
}
#endif // !BEHAVIOUR_ACTION_NODE_BASE_H