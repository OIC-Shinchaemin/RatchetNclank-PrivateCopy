#ifndef RATCHET_COMPONENT_ACTION_STATE_COMPONENT_H
#define RATCHET_COMPONENT_ACTION_STATE_COMPONENT_H


#include "UpdateComponent.h"

#include <optional>
#include <string>
#include <string_view>

#include "Base/Core/StateMachine.h"
#include "../State/ActionState.h"


namespace ratchet::component {
class ActionStateComponent : public ratchet::component::UpdateComponent {
    using super = ratchet::component::UpdateComponent;
private:
    //! �\��
    std::optional<std::string> _next_state;
protected:
    //! ���
    base::core::StateMachine _state_machine;
    //! �X�e�[�g,�R���|�[�l���g
    std::unordered_map<std::string, std::string> _action_map;
    /// <summary>
    /// �o�^
    /// </summary>
    /// <typeparam name="State"></typeparam>
    /// <param name="out"></param>
    void RegisterState(base::core::StateMachine& out, std::shared_ptr<ratchet::component::ActionComponent> com) {
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
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    const char* GetCurrentState(void) const;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name="state"></param>
    /// <returns></returns>
    bool IsEqual(std::string_view state) const;
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
    virtual std::shared_ptr<ratchet::component::Component> Clone(void) override;
    /// <summary>
    /// �ύX
    /// </summary>
    /// <param name="name"></param>
    void ChangeState(const std::string& name);
};
}
#endif // !RATCHET_COMPONENT_ACTION_STATE_COMPONENT_H