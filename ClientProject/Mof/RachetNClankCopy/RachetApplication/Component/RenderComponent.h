#ifndef MY_RENDER_COMPONENT_H
#define MY_RENDER_COMPONENT_H


#include "Component.h"


namespace my {
class RenderComponent : public my::Component {
    using super = my::Component;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    RenderComponent(int priority);
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
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool DebugRender(void);
};
}
#endif // !MY_RENDER_COMPONENT_H