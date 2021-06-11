#ifndef RATCHET_SHIP_IDLE_COMPONENT_H
#define RATCHET_SHIP_IDLE_COMPONENT_H


#include "ShipActionComponent.h"


namespace ratchet {
class ShipIdleComponent : public ratchet::ShipActionComponent {
    using super = ratchet::ShipActionComponent;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    ShipIdleComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    ShipIdleComponent(const ShipIdleComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~ShipIdleComponent();
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
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<ratchet::Component> Clone(void) override;
    /// <summary>
    /// �J�n
    /// </summary>
    /// <param name=""></param>
    /// <returns>����</returns>
    virtual bool Start(void) override;
};
}
#endif // !RATCHET_SHIP_IDLE_COMPONENT_H