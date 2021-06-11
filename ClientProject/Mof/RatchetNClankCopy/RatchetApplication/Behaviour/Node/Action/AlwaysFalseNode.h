#ifndef BEHAVIOUR_ALWAYS_FALSE_NODE_H
#define BEHAVIOUR_ALWAYS_FALSE_NODE_H


#include "../ActionNode.h"


namespace behaviour {
class AlwaysFalseNode : public behaviour::ActionNodeBase {
    using super = behaviour::ActionNodeBase;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    AlwaysFalseNode() :
        super("AlwaysFalseNode") {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~AlwaysFalseNode() = default;
    /// <summary>
    /// ノードの実行
    /// </summary>
    /// <param name="actor">実行アクター</param>
    /// <returns>true:実行の成功</returns>
    /// <returns>false:実行の失敗</returns>
    virtual bool Execute(std::any ptr) override {
        return false;
    }
};
}
#endif // !BEHAVIOUR_ALWAYS_FALSE_NODE_H