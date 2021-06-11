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
        return this->_name;
    }
    /// <summary>
    /// ノードの実行
    /// </summary>
    /// <param name="args"></param>
    /// <returns></returns>
    virtual bool Execute(std::any args) {
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