#ifndef RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_ACTION_COMPONENT_H
#define RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_ACTION_COMPONENT_H


#include "../ActionComponent.h"

#include <memory>

#include "../../Gamepad.h"
#include "../VelocityComponent.h"
#include "PlayerStateComponent.h"
#include "../MotionComponent.h"
#include "../MotionStateComponent.h"
#include "../../State/PlayerActionStateDefine.h"
#include "../../State/PlayerMotionStateDefine.h"


namespace ratchet {
namespace component {
namespace player {
namespace action {
class PlayerActionComponent : public ratchet::component::ActionComponent {
    using super = ratchet::component::ActionComponent;
private:
    //! ���x
    std::weak_ptr<ratchet::component::VelocityComponent> _velocity_com;
    //! ���
    std::weak_ptr<ratchet::component::player::PlayerStateComponent> _state_com;
    //! ���[�V����
    std::weak_ptr<ratchet::component::MotionComponent> _motion_com;
    //! ���[�V����
    std::weak_ptr<ratchet::component::MotionStateComponent> _motion_state_com;
protected:
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::component::VelocityComponent> GetVelocityComponent(void) const;
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
    PlayerActionComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    PlayerActionComponent(const PlayerActionComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~PlayerActionComponent();
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
}
}
}
#endif // !RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_ACTION_COMPONENT_H