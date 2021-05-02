#ifndef MY_SHIP_MESH_COMPONENT_H
#define MY_SHIP_MESH_COMPONENT_H


#include "../MeshComponent.h"


namespace my {
class ShipMeshComponent : public my::MeshComponent {
    using super = my::MeshComponent;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    ShipMeshComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    ShipMeshComponent(const ShipMeshComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~ShipMeshComponent();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
    /// <summary>
    /// 複製
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<my::Component> Clone(void) override;
};
}
#endif // !MY_MESH_COMPONENT_H