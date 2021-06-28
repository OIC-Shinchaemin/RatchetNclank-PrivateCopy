#ifndef RATCHET_COMPONENT_PLAYER_PLAYER_OMNI_WRENCH_COMPONENT_H
#define RATCHET_COMPONENT_PLAYER_PLAYER_OMNI_WRENCH_COMPONENT_H


#include "../UpdateComponent.h"


namespace ratchet {
namespace component {
namespace weapon { class OmniWrenchActionStateComponent; }
namespace collision { class OmniWrenchCollisionComponent; }
namespace player {
namespace action { class PlayerThrowAttackComponent; }

class PlayerOmniWrenchComponent : public ratchet::component::UpdateComponent {
    using super = ratchet::component::UpdateComponent;
private:
    //! ����
    std::weak_ptr<ratchet::actor::Actor> _weapon;
    //! ���
    std::weak_ptr<ratchet::component::player::action::PlayerThrowAttackComponent> _throw_attack_com;
    //! ���
    std::weak_ptr<ratchet::component::weapon::OmniWrenchActionStateComponent> _weapon_action_state_com;
    //! �Փː���
    std::weak_ptr<ratchet::component::collision::OmniWrenchCollisionComponent> _weapon_coll_com;
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
};
}
}
}
#endif // !RATCHET_COMPONENT_PLAYER_PLAYER_OMNI_WRENCH_COMPONENT_H