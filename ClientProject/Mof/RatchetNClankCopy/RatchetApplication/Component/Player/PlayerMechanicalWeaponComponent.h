#ifndef RATCHET_PLAYER_MECHANICAL_WEAPON_COMPONENT_H
#define RATCHET_PLAYER_MECHANICAL_WEAPON_COMPONENT_H


#include "../UpdateComponent.h"


namespace ratchet {
class PlayerMechanicalWeaponComponent : public ratchet::UpdateComponent {
    using super = ratchet::UpdateComponent;
private:
    //! ����
    std::weak_ptr<ratchet::Actor> _weapon;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    PlayerMechanicalWeaponComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    PlayerMechanicalWeaponComponent(const PlayerMechanicalWeaponComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~PlayerMechanicalWeaponComponent();
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
    /// �L����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Activate(void) override;
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Inactivate(void) override;
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
    virtual std::shared_ptr<ratchet::Component> Clone(void) override;
};
}
#endif // !RATCHET_PLAYER_MECHANICAL_WEAPON_COMPONENT_H