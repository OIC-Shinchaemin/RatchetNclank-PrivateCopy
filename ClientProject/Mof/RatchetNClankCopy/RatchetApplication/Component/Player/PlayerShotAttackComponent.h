#ifndef RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_SHOT_ATTACK_COMPONENT_H
#define RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_SHOT_ATTACK_COMPONENT_H


#include "PlayerActionComponent.h"

#include <memory>

#include "../../Actor/Weapon/Mechanical.h"


namespace ratchet {
namespace component {
namespace player {
namespace action {
class PlayerShotAttackComponent : public ::ratchet::component::player::action::PlayerActionComponent {
    using super = ::ratchet::component::player::action::PlayerActionComponent;
    struct InputInfo {
        Mof::CVector2 in;
        float move_angle = 0.0f;
        bool move_flag = false;
        void Reset(void) {
            in.x = 0.0f;
            in.y = 0.0f;
            move_angle = 0.0f;
            move_flag = false;
        }
    };
private:
    //! ����
    std::weak_ptr<::ratchet::actor::weapon::Mechanical> _weapon;
    //! ���͏��
    ratchet::component::player::action::PlayerShotAttackComponent::InputInfo _input_info;
    //! �ړ�
    std::weak_ptr<class PlayerMoveComponent> _move_com;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    PlayerShotAttackComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    PlayerShotAttackComponent(const PlayerShotAttackComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~PlayerShotAttackComponent();
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
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Input(void) override;
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
};
}
}
}
}
#endif // !RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_SHOT_ATTACK_COMPONENT_H