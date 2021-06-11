#ifndef RATCHET_SHIP_COMPONENT_H
#define RATCHET_SHIP_COMPONENT_H


#include "../UpdateComponent.h"

#include <memory>


namespace ratchet {
class ShipComponent : public ratchet::UpdateComponent{
    using super = ratchet::UpdateComponent;
private:
    //! ���[�V����
    std::weak_ptr<class MotionComponent> _motion_com;
    //! ���[�V����
    std::weak_ptr<class ShipStateComponent> _state_com;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    ShipComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    ShipComponent(const ShipComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~ShipComponent();
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
    /// �J�n
    /// </summary>
    /// <param name=""></param>
    /// <returns>����</returns>
    virtual bool Activate(void) override;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<ratchet::Component> Clone(void) override;
};
}
#endif // !RATCHET_SHIP_COMPONENT_H