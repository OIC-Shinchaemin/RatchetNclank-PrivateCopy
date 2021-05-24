#ifndef MY_PLAYER_MECHANICAL_WEAPON_COMPONENT_H
#define MY_PLAYER_MECHANICAL_WEAPON_COMPONENT_H


#include "../UpdateComponent.h"


namespace my {
class PlayerMechanicalWeaponComponent : public my::UpdateComponent {
    using super = my::UpdateComponent;
private:
    //! ����
    std::weak_ptr<my::Actor> _weapon;
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
    virtual std::shared_ptr<my::Component> Clone(void) override;
};
}
#endif // !MY_PLAYER_MECHANICAL_WEAPON_COMPONENT_H