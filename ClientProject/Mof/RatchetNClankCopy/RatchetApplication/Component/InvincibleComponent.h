#ifndef RATCHET_COMPONENT_PLAYER_INVINCIBLE_COMPONENT_H
#define RATCHET_COMPONENT_PLAYER_INVINCIBLE_COMPONENT_H


#include "UpdateComponent.h"

#include "Base/Core/Timer.h"


namespace ratchet::component {
class InvincibleComponent : public ratchet::component::UpdateComponent {
    using super = ratchet::component::UpdateComponent;
private:
    //! ����
    base::core::Timer _invincible;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    InvincibleComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    InvincibleComponent(const InvincibleComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~InvincibleComponent();
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
    /// �L����
    /// </summary>
    /// <param name=""></param>
    /// <returns>����</returns>
    virtual bool Activate(void) override;
};
}
#endif // !RATCHET_COMPONENT_PLAYER_INVINCIBLE_COMPONENT_H