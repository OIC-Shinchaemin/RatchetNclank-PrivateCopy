#ifndef BEHAVIOUR_INODE_EXECUTOR_H
#define BEHAVIOUR_INODE_EXECUTOR_H


#include <any>
#include <memory>
#include <list>

#include <Mof.h>


namespace behaviour {
// �O���錾
class INodeExecutor;
using NodeExecutorPtr = std::shared_ptr<INodeExecutor>;
using NodeExecutorWeakPtr = std::weak_ptr<INodeExecutor>;
using NodeExecutorList = std::list<NodeExecutorPtr>;
class INodeExecutor : public std::enable_shared_from_this<behaviour::INodeExecutor> {
public:
    enum class State {
        Inactive, //�����s
        Running, //���s��
        Completed, //���s�I��
        Incompleted, //���s���s
    };
    enum class Result {
        None, //�܂����s�O/���s��
        Sucess, //���s����
        Failure, //���s���s
    };
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    virtual void SetParent(behaviour::NodeExecutorWeakPtr ptr) = 0;
    /// <summary>
    /// ���s���K�v�ȃ|�C���^���L���b�V��
    /// </summary>
    /// <param actor=""></param>
    virtual void Prepare(std::any actor) = 0;
    /// <summary>
    /// �m�[�h�̎��s����
    /// </summary>
    /// <param name="actor">���s�A�N�^�[</param>
    /// <returns>Succeeded:���s�̐���</returns>
    /// <returns>Failed:���s�̎��s</returns>
    virtual INodeExecutor::Result Execute(void) = 0;
    /// <summary>
    /// ���s��Ԃ�S�ă��Z�b�g
    /// ��Ԃ�Inactive�ɐݒ�
    /// </summary>
    /// <param name=""></param>
    virtual void Reset(void) = 0;
    /// <summary>
    /// �f�o�b�O
    /// </summary>
    /// <typeparam name="Actor"></typeparam>
    virtual void DebugRender(Mof::CVector2 position) = 0;
    virtual void DebugRender(void) = 0;
};
}
#endif // !BEHAVIOUR_INODE_EXECUTOR_H