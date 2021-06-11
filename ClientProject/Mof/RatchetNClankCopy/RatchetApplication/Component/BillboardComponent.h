#ifndef RATCHET_BILLBOARD_COMPONENT_H
#define RATCHET_BILLBOARD_COMPONENT_H


#include "RenderComponent.h"

#include <memory>


namespace ratchet {
class BillboardComponent : public ratchet::RenderComponent {
    using super = ratchet::RenderComponent;
private:
    //! メッシュ
    std::weak_ptr<Mof::CTexture> _texture;
    //! 表示色
    Mof::CVector4 _color;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    BillboardComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    BillboardComponent(const BillboardComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~BillboardComponent();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="param"></param>
    virtual void SetParam(const rapidjson::Value& param) override;
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="mesh"></param>
    void SetTexture(const std::shared_ptr<Mof::CTexture>& ptr);
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
    std::shared_ptr<Mof::CTexture> GetTexture(void) const;
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
    virtual std::shared_ptr<ratchet::Component> Clone(void) override;
};
}
#endif // !RATCHET_BILLBOARD_COMPONENT_H