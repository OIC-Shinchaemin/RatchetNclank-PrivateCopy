#ifndef RATCHET_COMPONENT_EFFECT_SENSE_EFFECT_COMPONENT_H
#define RATCHET_COMPONENT_EFFECT_SENSE_EFFECT_COMPONENT_H


#include "../UpdateComponent.h"

#include <memory>

#include "../../Actor/Effect/SenseEffect.h"
#include "../BillboardComponent.h"
#include "Base/Core/Timer.h"


namespace ratchet::component::effect {
class SenseEffectComponent : public ::ratchet::component::UpdateComponent{
    using super = ::ratchet::component::UpdateComponent;
private:
    //! �`��I�t�Z�b�g
    Mof::CVector3 _billboard_render_offset;
    //! �r���{�[�h
    std::weak_ptr<ratchet::component::BillboardComponent> _billboard;
    //! ����
    base::core::Timer _timer;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    SenseEffectComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    SenseEffectComponent(const SenseEffectComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~SenseEffectComponent();
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
#ifdef _DEBUG
    /// <summary>
    /// �f�o�b�O
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool DebugRender(void) override;
#endif // _DEBUG
    void TimerStart(void);
};
}
#endif // !RATCHET_COMPONENT_EFFECT_SENSE_EFFECT_COMPONENT_H