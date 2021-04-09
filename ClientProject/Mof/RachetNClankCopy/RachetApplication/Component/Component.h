#ifndef MY_COMPONENT_H
#define MY_COMPONENT_H


#include <memory>

#include "rapidjson/document.h"

#include "../Actor.h"


namespace my {
class Component : public std::enable_shared_from_this<my::Component> {
private:
    //! ���̋@�\�̏��L��
    std::weak_ptr<my::Actor> _owner;
protected:
    //! �������قǏ�������鏇�Ԃ�����
    int _priority;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority">�D��x</param>
    Component(int priority);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Component();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetOwner(const std::shared_ptr<my::Actor>& ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="param"></param>
    virtual void SetParam(const rapidjson::Value& param);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const = 0;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<my::Actor> GetOwner(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    int GetPriority(void) const;
    /// <summary>
    /// ���͔���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool IsInput(void) const;
    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool IsUpdate(void) const;
    /// <summary>
    /// �`�攻��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool IsRender(void) const;
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void);
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Input(void);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time">����</param>
    /// <returns></returns>
    virtual bool Update(float delta_time);
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void);
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void);
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<my::Component> Clone(void) = 0;
};
static bool operator<(const my::Component& a, const my::Component& b) noexcept {
    return a.GetPriority() < b.GetPriority();
}
static bool operator<(const std::shared_ptr<my::Component>& a, const std::shared_ptr < my::Component>& b) noexcept {
    return a->GetPriority() < b->GetPriority();
}
}
#endif // !MY_COMPONENT_H