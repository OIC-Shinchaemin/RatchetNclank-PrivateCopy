#ifndef RATCHET_COMPONENT_BULLET_BLASTER_BULLET_COMPONENT_H
#define RATCHET_COMPONENT_BULLET_BLASTER_BULLET_COMPONENT_H


#include "../UpdateComponent.h"

#include <memory>


namespace ratchet::component::bullet {
class BlasterBulletComponent : public ::ratchet::component::UpdateComponent {
    using super = ::ratchet::component::UpdateComponent;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    BlasterBulletComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    BlasterBulletComponent(const BlasterBulletComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~BlasterBulletComponent();
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
#endif // !RATCHET_COMPONENT_BULLET_BLASTER_BULLET_COMPONENT_H