#ifndef MY_RENDER_COMPONENT_H
#define MY_RENDER_COMPONENT_H


#include "Component.h"

#include <string>


namespace my {
class RenderComponent : public my::Component {
    using super = my::Component;
protected:
    //! 描画リソース
    std::string _path;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    RenderComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    RenderComponent(const RenderComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~RenderComponent();
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
    std::string GetPath(void) const;
    /// <summary>
    /// 描画判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool IsRender(void) const override;
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
    /// デバッグ
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool DebugRender(void) override;
};
}
#endif // !MY_RENDER_COMPONENT_H