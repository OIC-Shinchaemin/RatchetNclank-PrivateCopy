#ifndef RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_DAMAGE_COMPONENT_H
#define RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_DAMAGE_COMPONENT_H


#include "PlayerActionComponent.h"

#include <memory>

#include "../HpComponent.h"


namespace ratchet ::component ::player ::action {
class PlayerDamageComponent : public ::ratchet::component::player::action::PlayerActionComponent {
    using super = ::ratchet::component::player::action::PlayerActionComponent;
private:
    //! 被弾量
    int _damage_value;
    //! 被弾速度
    float _damage_speed;
    //! 被弾角度
    Mof::CVector3 _damage_angle;
    //! Hp
    std::weak_ptr<::ratchet::component::HpComponent> _hp_com;

    /// <summary>
    /// 吹っ飛ぶ
    /// </summary>
    /// <param name=""></param>
    void DamegeAccele(void);
    /// <summary>
    /// ダメージ
    /// </summary>
    /// <param name=""></param>
    void Damege(void);
    /// <summary>
    /// 回復
    /// </summary>
    /// <param name=""></param>
    void Heal(void);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    PlayerDamageComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    PlayerDamageComponent(const PlayerDamageComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PlayerDamageComponent();
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
    virtual std::string_view GetStateType(void) const override;
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// 入力
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Input(void) override;
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
    /// <summary>
    /// 開始
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功</returns>
    virtual bool Start(void) override;
};
}
#endif // !RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_DAMAGE_COMPONENT_H