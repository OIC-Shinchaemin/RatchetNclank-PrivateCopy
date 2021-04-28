#ifndef MY_MESH_COMPONENT_H
#define MY_MESH_COMPONENT_H


#include "RenderComponent.h"

#include <vector>
#include <memory>


namespace my {
class MeshComponent : public my::RenderComponent {
    using super = my::RenderComponent;
private:
    //! メッシュ
    std::weak_ptr<Mof::CMeshContainer> _mesh;
    //! アニメーション
    std::weak_ptr<class MotionComponent> _motion_com;
    //! 非表示フラグ
    bool _is_show;
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
    void SetMesh(const std::shared_ptr<Mof::CMeshContainer>& ptr);
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
    std::weak_ptr<Mof::CMeshContainer> GetMesh(void) const;
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
    /// <summary>
    /// 表示しない
    /// </summary>
    /// <param name=""></param>
    void Hide(void);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool DebugRender(void) override;
};
}
#endif // !MY_MESH_COMPONENT_H