#ifndef BEHAVIOUR_ALWAYS_TRUE_NODE_H
#define BEHAVIOUR_ALWAYS_TRUE_NODE_H


#include "../ActionNode.h"


namespace behaviour {
template<typename Actor>
class AlwaysTrueNode : public behaviour::ActionNodeBase<Actor> {
    using super = behaviour::ActionNodeBase<Actor>;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    AlwaysTrueNode() :
        super("AlwaysTrueNode") {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~AlwaysTrueNode() = default;
    /// <summary>
    /// ノードの実行
    /// </summary>
    /// <param name="actor">実行アクター</param>
    /// <returns>true:実行の成功</returns>
    /// <returns>false:実行の失敗</returns>
    virtual bool Execute(Actor& actor) override {
        return true;
    }
};
}
#endif // !BEHAVIOUR_ALWAYS_TRUE_NODE_H