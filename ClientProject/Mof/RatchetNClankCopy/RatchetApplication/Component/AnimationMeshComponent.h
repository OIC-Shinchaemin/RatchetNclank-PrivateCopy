#ifndef RATCHET_COMPONENT_ANIMATION_MESH_COMPONENT_H
#define RATCHET_COMPONENT_ANIMATION_MESH_COMPONENT_H


#include "MeshComponent.h"

#include <memory>


namespace ratchet::component {
class AnimationMeshComponent : public ratchet::component::MeshComponent {
    using super = ratchet::component::MeshComponent;
protected:
    //! �A�j���[�V����
    std::weak_ptr<class MotionComponent> _motion_com;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    AnimationMeshComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    AnimationMeshComponent(const AnimationMeshComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~AnimationMeshComponent();
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
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(std::shared_ptr<ratchet::game::graphics::RenderCommandTask> out);
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
    virtual std::shared_ptr<ratchet::component::Component> Clone(void) override;
};
}
#endif // !RATCHET_COMPONENT_ANIMATION_MESH_COMPONENT_H