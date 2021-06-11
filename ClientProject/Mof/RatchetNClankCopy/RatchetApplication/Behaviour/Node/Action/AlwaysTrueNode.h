#ifndef RATCHET_BEHAVIOUR_ALWAYS_TRUE_NODE_H
#define RATCHET_BEHAVIOUR_ALWAYS_TRUE_NODE_H


#include "../ActionNode.h"


namespace ratchet {  namespace behaviour {
class AlwaysTrueNode : public ratchet::behaviour::ActionNodeBase {
    using super = ratchet::behaviour::ActionNodeBase;
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
    virtual bool Execute(std::any ptr) override {
        return true;
    }
};
}
}
#endif // !RATCHET_BEHAVIOUR_ALWAYS_TRUE_NODE_H