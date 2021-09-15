#ifndef RATCHET_FACTORY_BUILDER_SCENE_SCENE_BUILDER_H
#define RATCHET_FACTORY_BUILDER_SCENE_SCENE_BUILDER_H


#include "../IBuilder.h"

#include <memory>

#include "../../../Scene/Scene.h"
#include "../../../ResourceManager.h"
#include "../../../GameDefine.h"
#include "Base/UI/UICanvas.h"


namespace ratchet::factory::builder::scene {
class SceneBuilder : public ratchet::factory::builder::IBuilder {
    using super = ratchet::factory::builder::IBuilder;
private:
    //! ���\�[�X
    std::weak_ptr<ratchet::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<base::ui::UICanvas> _ui_canvas;
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
    void SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr);
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
#endif // !RATCHET_FACTORY_BUILDER_SCENE_SCENE_BUILDER_H