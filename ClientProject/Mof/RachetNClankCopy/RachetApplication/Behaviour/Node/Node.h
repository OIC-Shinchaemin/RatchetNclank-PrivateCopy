#ifndef BEHAVIOUR_NODE_H
#define BEHAVIOUR_NODE_H


#include <any>

#include "../Executor/INodeExecutor.h"


namespace behaviour {
class Node : public std::enable_shared_from_this<behaviour::Node> {
protected:
    //! ���O
    std::string _name;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="name"></param>
    Node(const std::string& name)
        : _name(name) {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Node() = default;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    const std::string& GetName(void)const noexcept {
        return _name;
    }
    /// <summary>
    /// �m�[�h�̎��s
    /// </summary>
    /// <param name="actor">���s�A�N�^�[</param>
    /// <returns>true:���s�̐���</returns>
    /// <returns>false:���s�̎��s</returns>
    virtual bool Execute(std::any ptr) {
        return false;
    }
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual behaviour::NodeExecutorPtr CreateExecutor(void) const = 0;
};
using NodePtr = std::shared_ptr<Node>;
using NodeList = std::list<NodePtr>;
}
#endif // !BEHAVIOUR_NODE_H