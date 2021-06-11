#ifndef RACHET_RENDER_COMPONENT_H
#define RACHET_RENDER_COMPONENT_H


#include "Component.h"

#include <string>


namespace rachet {
class RenderComponent : public rachet::Component {
    using super = rachet::Component;
protected:
    //! ���\�[�X
    std::string _path;
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
#endif // !RACHET_RENDER_COMPONENT_H