#ifndef BUILDER_SCENE_BUILDER_H
#define BUILDER_SCENE_BUILDER_H


#include "../IBuilder.h"

#include <memory>

#include "../../../Scene/Scene.h"
#include "../../../ResourceManager.h"
#include "../../../GameDefine.h"
#include "Base/UI/UICanvas.h"


namespace builder {
class SceneBuilder : public ratchet::IBuilder {
    using super = ratchet::IBuilder;
private:
    //! リソース
    std::weak_ptr<ratchet::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<base::ui::UICanvas> _ui_canvas;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    SceneBuilder();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~SceneBuilder();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr);
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    virtual void Release(void);
    /// <summary>
    /// 構築
    /// </summary>
    /// <param name=""></param>
    virtual void Construct(std::any shared_this) override;
};
}
#endif // !BUILDER_SCENE_BUILDER_H