#ifndef RACHET_MESH_COMPONENT_H
#define RACHET_MESH_COMPONENT_H


#include "RenderComponent.h"

#include <memory>


namespace rachet {
class MeshComponent : public rachet::RenderComponent {
    using super = rachet::RenderComponent;
private:
    //! メッシュ
    std::weak_ptr<Mof::CMeshContainer> _mesh;
    //! 表示色
    Mof::CVector4 _color;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    MeshComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    MeshComponent(const MeshComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~MeshComponent();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="param"></param>
    virtual void SetParam(const rapidjson::Value& param) override;
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="mesh"></param>
    void SetMeshContainer(const std::shared_ptr<Mof::CMeshContainer>& ptr);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<Mof::CMeshContainer> GetMeshContainer(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector4 GetColor(void) const;
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
    virtual std::shared_ptr<rachet::Component> Clone(void) override;
};
}
#endif // !RACHET_MESH_COMPONENT_H