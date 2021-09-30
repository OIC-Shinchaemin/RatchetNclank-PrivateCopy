#ifndef RATCHET_COMPONENT_RENDER_COMPONENT_H
#define RATCHET_COMPONENT_RENDER_COMPONENT_H


#include "Component.h"

#include <string>


namespace ratchet::component {
class RenderComponent : public ratchet::component::Component {
    using super = ratchet::component::Component;
protected:
    //! ���\�[�X
    std::string _path;
    //! 
    std::uint32_t _target_layer;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    RenderComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    RenderComponent(const RenderComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~RenderComponent();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="param"></param>
    virtual void SetParam(const rapidjson::Value& param) override;
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="layer"></param>
    void SetTargetLayer(std::uint32_t layer);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::string GetPath(void) const;
    /// <summary>
    /// �`�攻��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool IsRender(void) const override;
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
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
};
}
#endif // !RATCHET_COMPONENT_RENDER_COMPONENT_H