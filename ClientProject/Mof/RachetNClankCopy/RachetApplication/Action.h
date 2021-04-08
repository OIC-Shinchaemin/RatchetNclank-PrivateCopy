#ifndef MY_ACTION_H
#define MY_ACTION_H


#include <memory>


namespace my {
class Action : public std::enable_shared_from_this<my::Action> {
protected:
    //! ���L��
    std::weak_ptr<class Enemy> _owner;
    //! �L��
    bool _active;
    //! �X�V��
    int _priority;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool InactiveCondition(void) const = 0;
    /// <summary>
    /// ���s
    /// </summary>
    /// <param name="delta_time"></param>
    virtual void Execute(float delta_time) = 0;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Action();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Action();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="owner"></param>
    void SetOwner(const std::shared_ptr<class Enemy>& ptr);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<class Enemy> GetOwner(void) const;
    /// <summary>
    /// �L������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool IsActive(void) const;
    /// <summary>
    /// ���s
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    bool Update(float delta_time);
    /// <summary>
    /// �J�n
    /// </summary>
    /// <param name=""></param>
    /// <returns>����</returns>
    virtual bool Start(void);
};
}
#endif // !MY_ACTION_H