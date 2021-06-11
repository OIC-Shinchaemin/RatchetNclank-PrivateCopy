#ifndef RATCHET_SHIP_LANDING_COMPONENT_H
#define RATCHET_SHIP_LANDING_COMPONENT_H


#include "ShipActionComponent.h"
#include "Base/Core/Observable.h"

#include "../../Camera/CameraController.h"


namespace ratchet {
class ShipLandingComponent : public ratchet::ShipActionComponent,
    public base::core::Observable<const ratchet::camera::CameraController::CameraInfo&> {
    using super = ratchet::ShipActionComponent;
    using Observable = base::core::Observable<const ratchet::camera::CameraController::CameraInfo&>;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    ShipLandingComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    ShipLandingComponent(const ShipLandingComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~ShipLandingComponent();
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
    /// �ǉ�
    /// </summary>
    /// <param name="ptr"></param>
    void AddObserver(const std::shared_ptr<base::core::Observer<const ratchet::camera::CameraController::CameraInfo&>>& ptr);
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
    /// <summary>
    /// �I��
    /// </summary>
    /// <param name=""></param>
    /// <returns>����</returns>
    virtual bool End(void) override;
};
}
#endif // !RATCHET_SHIP_LANDING_COMPONENT_H