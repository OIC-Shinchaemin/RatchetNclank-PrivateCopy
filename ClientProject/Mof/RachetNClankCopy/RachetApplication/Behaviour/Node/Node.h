#ifndef BEHAVIOUR_NODE_H
#define BEHAVIOUR_NODE_H


#include <any>

#include "../Executor/INodeExecutor.h"


namespace behaviour {
class Node : public std::enable_shared_from_this<behaviour::Node> {
protected:
    //! 名前
    std::string _name;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="name"></param>
    Node(const std::string& name)
        : _name(name) {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Node() = default;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    const std::string& GetName(void)const noexcept {
        return _name;
    }
    /// <summary>
    /// ノードの実行
    /// </summary>
    /// <param name="actor">実行アクター</param>
    /// <returns>true:実行の成功</returns>
    /// <returns>false:実行の失敗</returns>
    virtual bool Execute(std::any ptr) {
        return false;
    }
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual behaviour::NodeExecutorPtr CreateExecutor(void) const = 0;
};
using NodePtr = std::shared_ptr<Node>;
using NodeList = std::list<NodePtr>;
}
#endif // !BEHAVIOUR_NODE_H