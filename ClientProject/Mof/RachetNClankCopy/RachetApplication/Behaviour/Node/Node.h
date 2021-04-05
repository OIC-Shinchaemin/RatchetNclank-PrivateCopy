#ifndef BEHAVIOUR_NODE_H
#define BEHAVIOUR_NODE_H


#include "../Executor/INodeExecutor.h"


namespace behaviour {
// �O���錾
template<typename Actor> class Node;
template<typename Actor> using NodePtr = std::shared_ptr<Node<Actor>>;
template<typename Actor> using NodeList = std::list<NodePtr<Actor>>;
template<typename Actor>
class Node : public std::enable_shared_from_this<Node<Actor>> {
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
    const std::string& GetName(void)const noexcept { return _name; }
    /// <summary>
    /// �m�[�h�̎��s
    /// </summary>
    /// <param name="actor">���s�A�N�^�[</param>
    /// <returns>true:���s�̐���</returns>
    /// <returns>false:���s�̎��s</returns>
    virtual bool Execute(Actor& actor) { return false; }
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual behaviour::NodeExecutorPtr<Actor> CreateExecutor(void) const = 0;
};
}
#endif // !BEHAVIOUR_NODE_H