#ifndef RACHET_SHIP_ACTION_COMPONENT_H
#define RACHET_SHIP_ACTION_COMPONENT_H


#include "../ActionComponent.h"

#include <memory>

#include "../../Gamepad.h"
#include "../VelocityComponent.h"
#include "ShipStateComponent.h"
#include "../MotionComponent.h"
#include "../MotionStateComponent.h"
#include "../../State/ShipActionStateDefine.h"
#include "../../State/ShipMotionStateDefine.h"


namespace rachet {
class ShipActionComponent : public rachet::ActionComponent {
    using super = rachet::ActionComponent;
private:
    //! ���x
    std::weak_ptr<rachet::VelocityComponent> _velocity_com;
    //! ���
    std::weak_ptr<rachet::ShipStateComponent> _state_com;
    //! ���[�V����
    std::weak_ptr<rachet::MotionComponent> _motion_com;
    //! ���[�V����
    std::weak_ptr<rachet::MotionStateComponent> _motion_state_com;
protected:
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<rachet::VelocityComponent> GetVelocityComponent(void) const;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool IsEndMotion(void) const;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name="next"></param>
    /// <returns></returns>
    bool CanTransitionActionState(const std::string& next) const;
    /// <summary>
    /// �ύX
    /// </summary>
    /// <param name="name"></param>
    bool ChangeActionState(const std::string& name);
    /// <summary>
    /// �ύX
    /// </summary>
    /// <param name="name"></param>
    bool ChangeMotionState(const std::string& name);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    ShipActionComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    ShipActionComponent(const ShipActionComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~ShipActionComponent();
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
#endif // !RACHET_SHIP_ACTION_COMPONENT_H