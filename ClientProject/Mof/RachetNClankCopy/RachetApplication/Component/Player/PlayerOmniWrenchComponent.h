#ifndef MY_PLAYER_OMNI_WRENCH_COMPONENT_H
#define MY_PLAYER_OMNI_WRENCH_COMPONENT_H


#include "../UpdateComponent.h"


namespace my {
class PlayerOmniWrenchComponent : public my::UpdateComponent {
    using super = my::UpdateComponent;
private:
    //! ����
    std::weak_ptr<my::Actor> _weapon;
    //! ���
    std::weak_ptr<class PlayerThrowAttackComponent> _throw_attack_com;
    //! ���
    std::weak_ptr<class OmniWrenchActionStateComponent> _weapon_action_state_com;
    //! �Փː���
    std::weak_ptr<class OmniWrenchCollisionComponent> _weapon_coll_com;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    PlayerOmniWrenchComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    PlayerOmniWrenchComponent(const PlayerOmniWrenchComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~PlayerOmniWrenchComponent();
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
#endif // !MY_PLAYER_OMNI_WRENCH_COMPONENT_H