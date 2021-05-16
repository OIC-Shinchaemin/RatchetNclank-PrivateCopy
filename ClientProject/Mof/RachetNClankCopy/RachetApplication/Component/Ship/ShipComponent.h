#ifndef MY_SHIP_COMPONENT_H
#define MY_SHIP_COMPONENT_H


#include "../UpdateComponent.h"

#include <memory>

#include "My/Core/Timer.h"
#include "My/Core/ServiceLocator.h"
#include "../../Camera/Camera.h"
#include "../../Camera/CameraController.h"


namespace my {
class ShipComponent : public my::UpdateComponent {
    using super = my::UpdateComponent;
private:
    //! �^�C�}�[
    my::Timer _timer;
    //! �t���O
    bool _take_off;
    //! �J�����R���g���[��
    my::ServiceLocator<my::CameraController> _camera_controller;
    //! ���[�V����
    std::weak_ptr<class MotionComponent> _motion_com;
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
    virtual std::shared_ptr<my::Component> Clone(void) override;
};
}
#endif // !MY_SHIP_COMPONENT_H