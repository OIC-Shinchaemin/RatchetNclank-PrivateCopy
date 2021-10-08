#ifndef RATCHET_COMPONENT_ENEMY_HP_BILLBOARD_COMPONENT_H
#define RATCHET_COMPONENT_ENEMY_HP_BILLBOARD_COMPONENT_H


#include "../RenderComponent.h"

#include <memory>

#include "../HpComponent.h"
#include "EnemyComponent.h"


namespace ratchet::component::enemy {
class EnemyHpBillboardComponent : public ratchet::component::RenderComponent {
    using super = ratchet::component::RenderComponent;
private:
    //! ゲージ部分
    std::string _path2;
    //! 
    std::weak_ptr<Mof::CTexture> _texture;
    //! 
    std::weak_ptr<Mof::CTexture> _texture_hp_guage;
    //! 表示色
    Mof::CVector4 _color;
    //! オフセット
    Mof::CVector3 _offset_position;
    //! オフセット
    Mof::CVector3 _offset_rotation;
    //! hp
    std::weak_ptr<component::HpComponent> _hp_com;
    //! hp
    std::weak_ptr<component::enemy::EnemyComponent> _type_com;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    EnemyHpBillboardComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    EnemyHpBillboardComponent(const EnemyHpBillboardComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~EnemyHpBillboardComponent();
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
    /// セッター
    /// </summary>
    /// <param name="value"></param>
    void SetColor(const Mof::CVector4& value);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="value"></param>
    void SetOffsetPosition(const Mof::CVector3& value);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="value"></param>
    void SetOffsetRotation(const Mof::CVector3& value);
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
#endif // !RATCHET_COMPONENT_ENEMY_HP_BILLBOARD_COMPONENT_H