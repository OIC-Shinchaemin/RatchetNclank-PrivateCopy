#ifndef RATCHET_COMPONENT_WEAPON_OMNI_WRENCH_DEFAULT_COMPONENT_H
#define RATCHET_COMPONENT_WEAPON_OMNI_WRENCH_DEFAULT_COMPONENT_H


#include "../../ActionComponent.h"

#include <memory>

#include "../../VelocityComponent.h"


namespace ratchet {
namespace component {
namespace weapon {
class OmniWrenchDefaultComponent : public ratchet::component::ActionComponent {
    using super = ratchet::component::ActionComponent;
private:
    //! ���x
    std::weak_ptr<ratchet::component::VelocityComponent> _velocity_com;
    //! ���
    std::weak_ptr<class OmniWrenchActionStateComponent > _action_state_com;
    /// <summary>
    /// �ύX
    /// </summary>
    /// <param name="name"></param>
    void ChageState(const std::string& name);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    OmniWrenchDefaultComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    OmniWrenchDefaultComponent(const OmniWrenchDefaultComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~OmniWrenchDefaultComponent();
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
    virtual std::string_view GetStateType(void) const override;
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time">����</param>
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
    /// �J�n
    /// </summary>
    /// <param name=""></param>
    /// <returns>����</returns>
    virtual bool Start(void) override;
    /// <summary>
    /// �I��
    /// </summary>
    /// <param name=""></param>
    /// <returns>����</returns>
    virtual bool End(void) override;
};
}
}
}
#endif // !RATCHET_COMPONENT_WEAPON_OMNI_WRENCH_DEFAULT_COMPONENT_H