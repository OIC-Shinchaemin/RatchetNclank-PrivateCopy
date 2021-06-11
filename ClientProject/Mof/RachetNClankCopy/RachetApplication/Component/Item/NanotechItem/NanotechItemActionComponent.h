#ifndef RATCHET_NanotechItem_ACTION_COMPONENT_H
#define RATCHET_NanotechItem_ACTION_COMPONENT_H


#include "../../ActionComponent.h"

#include <memory>

#include "../../VelocityComponent.h"
#include "NanotechItemActionStateComponent.h"
#include "../../../State/NanotechItemActionStateDefine.h"


namespace ratchet {
class NanotechItemActionComponent : public ratchet::ActionComponent {
    using super = ratchet::ActionComponent;
private:
    //! ���x
    std::weak_ptr<ratchet::VelocityComponent> _velocity_com;
    //! ���
    std::weak_ptr<ratchet::NanotechItemActionStateComponent> _state_com;
protected:
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::VelocityComponent> GetVelocityComponent(void) const;
    /// <summary>
    /// �ύX
    /// </summary>
    /// <param name="name"></param>
    bool ChangeActionState(const std::string& name);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    NanotechItemActionComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    NanotechItemActionComponent(const NanotechItemActionComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~NanotechItemActionComponent();
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
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
};
}
#endif // !RATCHET_NanotechItem_ACTION_COMPONENT_H