#ifndef RATCHET_COMPONENT_SCARECROW_SCARECROW_COMPONENT_H
#define RATCHET_COMPONENT_SCARECROW_SCARECROW_COMPONENT_H


#include "../CharacterComponent.h"

#include <memory>

#include "../../Actor/Actor.h"
#include "Base/Core/Observable.h"
#include "../../Effect/EffectEmitter.h"


namespace ratchet::component { 
class  HpComponent; 
class  InvincibleComponent;
}
namespace ratchet::component::scarecrow {
class ScarecrowComponent : public ::ratchet::component::CharacterComponent {
    using super = ::ratchet::component::CharacterComponent;
private:
    //! Hp
    std::weak_ptr<ratchet::component::HpComponent> _hp_com;
    //! ���G
    std::weak_ptr<ratchet::component::InvincibleComponent> _invincible_com;

    /// <summary>
    /// �G�t�F�N�g����
    /// </summary>
    /// <param name=""></param>
    void DamageEffectEmit(std::shared_ptr<ratchet::actor::Actor> actor);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    ScarecrowComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    ScarecrowComponent(const ScarecrowComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~ScarecrowComponent();
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
    virtual std::shared_ptr<::ratchet::component::Component> Clone(void) override;
};
}
#endif // !RATCHET_COMPONENT_SCARECROW_SCARECROW_COMPONENT_H