#ifndef MY_ACTION_STATE_COMPONENT_H
#define MY_ACTION_STATE_COMPONENT_H


#include "UpdateComponent.h"

#include "My/Core/StateMachine.h"
#include "../State/ActionState.h"


namespace my {
class ActionStateComponent : public my::UpdateComponent {
    using super = my::UpdateComponent;
private:
    //! ���
    my::StateMachine _state_machine;
    /// <summary>
    /// �o�^
    /// </summary>
    /// <typeparam name="State"></typeparam>
    /// <param name="out"></param>
    void RegisterState(my::StateMachine& out, std::shared_ptr<my::ActionComponent> com) {
        auto shared_this = super::GetOwner();
        auto ptr = std::make_shared<state::ActionState>();
        ptr->SetActionComponent(com);
        out.RegisterState(ptr);
    }
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    ActionStateComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    ActionStateComponent(const ActionStateComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~ActionStateComponent();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="param"></param>
    virtual void SetParam(const rapidjson::Value& param) override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<my::Component> Clone(void) override;
    /// <summary>
    /// �ύX
    /// </summary>
    /// <param name="name"></param>
    void ChangeState(const std::string& name);
};
}
#endif // !MY_ACTION_STATE_COMPONENT_H