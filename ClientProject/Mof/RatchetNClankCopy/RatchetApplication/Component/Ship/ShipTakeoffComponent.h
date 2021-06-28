#ifndef RATCHET_COMPONENT_SHIP_SHIP_TAKEOFF_COMPONENT_H
#define RATCHET_COMPONENT_SHIP_SHIP_TAKEOFF_COMPONENT_H


#include "ShipActionComponent.h"

#include <memory>

#include "Base/Core/Timer.h"


namespace ratchet {
namespace component {
namespace ship {
class ShipTakeoffComponent : public ratchet::component::ship::ShipActionComponent {
    using super = ratchet::component::ship::ShipActionComponent;
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
    virtual std::shared_ptr<ratchet::component::Component> Clone(void) override;
    /// <summary>
    /// �J�n
    /// </summary>
    /// <param name=""></param>
    /// <returns>����</returns>
    virtual bool Start(void) override;
};
}
}
}
#endif // !RATCHET_COMPONENT_SHIP_SHIP_TAKEOFF_COMPONENT_H