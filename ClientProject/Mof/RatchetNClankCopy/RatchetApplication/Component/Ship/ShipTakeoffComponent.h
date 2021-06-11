#ifndef RATCHET_SHIP_TAKEOFF_COMPONENT_H
#define RATCHET_SHIP_TAKEOFF_COMPONENT_H


#include "ShipActionComponent.h"

#include <memory>

#include "Base/Core/Timer.h"


namespace ratchet {
class ShipTakeoffComponent : public ratchet::ShipActionComponent {
    using super = ratchet::ShipActionComponent;
private:
    //! �^�C�}�[
    base::core::Timer _timer;
    //! �㏸
    bool _takeoff;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    ShipTakeoffComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    ShipTakeoffComponent(const ShipTakeoffComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~ShipTakeoffComponent();
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
#endif // !RATCHET_SHIP_TAKEOFF_COMPONENT_H