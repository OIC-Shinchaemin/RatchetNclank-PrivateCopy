#ifndef RATCHET_COMPONENT_ANIMATION_MESH_COMPONENT_H
#define RATCHET_COMPONENT_ANIMATION_MESH_COMPONENT_H


#include "MeshComponent.h"

#include <memory>


namespace ratchet::component {
class AnimationMeshComponent : public ratchet::component::MeshComponent {
    using super = ratchet::component::MeshComponent;
protected:
    //! アニメーション
    std::weak_ptr<class MotionComponent> _motion_com;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    AnimationMeshComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    AnimationMeshComponent(const AnimationMeshComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~AnimationMeshComponent();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(std::shared_ptr<ratchet::game::graphics::RenderCommandTask> out);
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
    /// <summary>
    /// 複製
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<ratchet::component::Component> Clone(void) override;
};
}
#endif // !RATCHET_COMPONENT_ANIMATION_MESH_COMPONENT_H