#ifndef MY_PLAYER_DAMAGE_COMPONENT_H
#define MY_PLAYER_DAMAGE_COMPONENT_H


#include "PlayerActionComponent.h"

#include <memory>


namespace my {
class PlayerDamageComponent : public my::PlayerActionComponent {
    using super = my::PlayerActionComponent;
private:
    //! ��e��
    int _damage_value;
    //! ��e���x
    float _damage_speed;
    //! ��e�p�x
    Mof::CVector3 _damage_angle;
    //! Hp
    std::weak_ptr<class HpComponent> _hp_com;
    /// <summary>
    /// �������
    /// </summary>
    /// <param name=""></param>
    void DamegeAccele(void);
    /// <summary>
    /// �_���[�W
    /// </summary>
    /// <param name=""></param>
    void Damege(void);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    PlayerDamageComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    PlayerDamageComponent(const PlayerDamageComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~PlayerDamageComponent();
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
};
}
#endif // !MY_PLAYER_DAMAGE_COMPONENT_H