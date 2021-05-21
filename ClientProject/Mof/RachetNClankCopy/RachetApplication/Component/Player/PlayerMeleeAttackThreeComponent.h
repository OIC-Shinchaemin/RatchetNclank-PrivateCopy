#ifndef MY_PLAYER_MELEE_ATTACK_THREE_COMPONENT_H
#define MY_PLAYER_MELEE_ATTACK_THREE_COMPONENT_H


#include "PlayerActionComponent.h"

#include <memory>


namespace my {
class PlayerMeleeAttackThreeComponent : public my::PlayerActionComponent {
    using super = my::PlayerActionComponent;
private:
    //! �ړ�
    std::weak_ptr<class PlayerMoveComponent> _move_com;
    //! ����
    std::weak_ptr<class PlayerWeaponComponent> _weapon_com;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    PlayerMeleeAttackThreeComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    PlayerMeleeAttackThreeComponent(const PlayerMeleeAttackThreeComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~PlayerMeleeAttackThreeComponent();
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
    virtual std::shared_ptr<my::Component> Clone(void) override;
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
#endif // !MY_PLAYER_MELEE_ATTACK_THREE_COMPONENT_H