#ifndef RATCHET_COMPONENT_SCARECROW_SCARECROW_COMPONENT_H
#define RATCHET_COMPONENT_SCARECROW_SCARECROW_COMPONENT_H


#include "../CharacterComponent.h"

#include <memory>

#include "../../Actor/Actor.h"
#include "Base/Core/Observable.h"
#include "../../Effect/EffectEmitter.h"


namespace ratchet::component { 
class  HpComponent; 
class  InvincibleComponent;
}
namespace ratchet::component::scarecrow {
class ScarecrowComponent : public ::ratchet::component::CharacterComponent {
    using super = ::ratchet::component::CharacterComponent;
private:
    //! Hp
    std::weak_ptr<ratchet::component::HpComponent> _hp_com;
    //! 無敵
    std::weak_ptr<ratchet::component::InvincibleComponent> _invincible_com;

    /// <summary>
    /// エフェクト発生
    /// </summary>
    /// <param name=""></param>
    void DamageEffectEmit(std::shared_ptr<ratchet::actor::Actor> actor);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    ScarecrowComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    ScarecrowComponent(const ScarecrowComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~ScarecrowComponent();
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
    /// 更新
    /// </summary>
    /// <param name="delta_time">時間</param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
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
    virtual std::shared_ptr<::ratchet::component::Component> Clone(void) override;
};
}
#endif // !RATCHET_COMPONENT_SCARECROW_SCARECROW_COMPONENT_H