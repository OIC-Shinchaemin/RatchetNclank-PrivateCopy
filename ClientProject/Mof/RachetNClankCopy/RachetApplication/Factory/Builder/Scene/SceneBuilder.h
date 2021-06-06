#ifndef BUILDER_SCENE_BUILDER_H
#define BUILDER_SCENE_BUILDER_H


#include "../IBuilder.h"

#include <memory>

#include "../../../Scene/Scene.h"
#include "../../../ResourceManager.h"
#include "../../../GameDefine.h"
#include "My/UI/UICanvas.h"


namespace builder {
class SceneBuilder : public my::IBuilder {
    using super = my::IBuilder;
private:
    //! リソース
    std::weak_ptr<my::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<my::UICanvas> _ui_canvas;
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
    void SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetUICanvas(std::weak_ptr<my::UICanvas> ptr);
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