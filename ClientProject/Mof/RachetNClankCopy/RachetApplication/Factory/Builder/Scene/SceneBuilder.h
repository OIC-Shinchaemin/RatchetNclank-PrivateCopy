#ifndef BUILDER_SCENE_BUILDER_H
#define BUILDER_SCENE_BUILDER_H


#include "../IBuilder.h"

#include <memory>

#include "../../../Scene/Scene.h"
#include "../../../ResourceManager.h"
#include "../../../GameDefine.h"


namespace builder {
class SceneBuilder : public my::IBuilder {
    using super = my::IBuilder;
private:
    //! ���\�[�X
    std::weak_ptr<my::ResourceMgr> _resource;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    SceneBuilder();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~SceneBuilder();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr);
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    virtual void Release(void);
    /// <summary>
    /// �\�z
    /// </summary>
    /// <param name=""></param>
    virtual void Construct(std::any shared_this) override;
};
}
#endif // !BUILDER_SCENE_BUILDER_H