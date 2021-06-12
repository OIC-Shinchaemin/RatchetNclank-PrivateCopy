#ifndef RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_THROW_ATTACK_END_COMPONENT_H
#define RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_THROW_ATTACK_END_COMPONENT_H


#include "PlayerActionComponent.h"

#include <memory>


namespace ratchet {
namespace component {
namespace player {
class PlayerOmniWrenchComponent;
namespace action {
class PlayerThrowAttackEndComponent : public ratchet::component::player::action::PlayerActionComponent {
    using super = ratchet::component::player::action::PlayerActionComponent;
private:
    //! ����
    std::weak_ptr<ratchet::component::player::PlayerOmniWrenchComponent> _weapon_com;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    PlayerThrowAttackEndComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    PlayerThrowAttackEndComponent(const PlayerThrowAttackEndComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~PlayerThrowAttackEndComponent();
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
#endif // !RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_THROW_ATTACK_END_COMPONENT_H