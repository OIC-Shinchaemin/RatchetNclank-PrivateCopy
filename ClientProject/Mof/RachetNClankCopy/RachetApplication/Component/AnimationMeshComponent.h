#ifndef MY_ANIMATION_MESH_COMPONENT_H
#define MY_ANIMATION_MESH_COMPONENT_H


#include "MeshComponent.h"

#include <memory>


namespace my {
class AnimationMeshComponent : public my::MeshComponent {
    using super = my::MeshComponent;
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
    virtual std::shared_ptr<my::Component> Clone(void) override;
};
}
#endif // !MY_ANIMATION_MESH_COMPONENT_H