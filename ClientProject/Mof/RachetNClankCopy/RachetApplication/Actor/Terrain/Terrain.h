#ifndef MY_TERRAIN_H
#define MY_TERRAIN_H


#include "../../Actor.h"
#include "../../GameDefine.h"
#include "../../ResourceManager.h"


namespace my {
class Terrain : public my::Actor {
    using super = my::Actor;
private:
    //! 水面
    Mof::LPGeometry _plane;
    //! スクロール
    my::cbUVScrollParam _uv_scroll;
    //! スクロール
    Mof::CVector2 _scroll_increase;
    //シェーダー
    Mof::CShader _shader;
    Mof::CShaderBind_3DPrimitiveBase _shader_bind;
    //! リソース
    std::weak_ptr<my::ResourceMgr> _resource;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Terrain();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Terrain();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="param"></param>
    /// <returns></returns>
    virtual bool Initialize(my::Actor::Param* param) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
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
};
}
#endif // !MY_TERRAIN_H