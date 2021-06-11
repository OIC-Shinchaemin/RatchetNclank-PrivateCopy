#ifndef RATCHET_SHIP_MESH_COMPONENT_H
#define RATCHET_SHIP_MESH_COMPONENT_H


#include "../AnimationMeshComponent.h"


namespace ratchet {
class ShipMeshComponent : public ratchet::AnimationMeshComponent {
    using super = ratchet::AnimationMeshComponent;
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
    virtual std::shared_ptr<ratchet::component::Component> Clone(void) override;
};
}
#endif // !RATCHET_SHIP_MESH_COMPONENT_H