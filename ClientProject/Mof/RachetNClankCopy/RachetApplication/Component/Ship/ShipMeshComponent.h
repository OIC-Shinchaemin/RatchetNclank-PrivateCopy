#ifndef MY_SHIP_MESH_COMPONENT_H
#define MY_SHIP_MESH_COMPONENT_H


#include "../AnimationMeshComponent.h"


namespace my {
class ShipMeshComponent : public my::AnimationMeshComponent {
    using super = my::AnimationMeshComponent;
private:
    //! メッシュ
    Mof::LPMesh _ship_mesh;
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
    /// セッター
    /// </summary>
    /// <param name="param"></param>
    virtual void SetParam(const rapidjson::Value& param) override;
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
#endif // !MY_SHIP_MESH_COMPONENT_H