#ifndef MY_SHIP_LANDING_COMPONENT_H
#define MY_SHIP_LANDING_COMPONENT_H


#include "ShipActionComponent.h"
#include "Base/Core/Observable.h"

#include "../../Camera/CameraController.h"


namespace my {
class ShipLandingComponent : public my::ShipActionComponent,
    public my::Observable<const my::CameraController::CameraInfo&> {
    using super = my::ShipActionComponent;
    using Observable = my::Observable<const my::CameraController::CameraInfo&>;
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
    void AddObserver(const std::shared_ptr<my::Observer<const my::CameraController::CameraInfo&>>& ptr);
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
    virtual std::shared_ptr<my::Component> Clone(void) override;
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
#endif // !MY_SHIP_LANDING_COMPONENT_H