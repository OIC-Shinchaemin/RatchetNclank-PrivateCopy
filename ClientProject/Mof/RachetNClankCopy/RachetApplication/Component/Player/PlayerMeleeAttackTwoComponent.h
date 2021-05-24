#ifndef MY_PLAYER_MELEE_ATTACK_TWO_COMPONENT_H
#define MY_PLAYER_MELEE_ATTACK_TWO_COMPONENT_H


#include "PlayerActionComponent.h"

#include <memory>


namespace my {
class PlayerMeleeAttackTwoComponent : public my::PlayerActionComponent {
    using super = my::PlayerActionComponent;
private:
    //! 予約
    bool _next_reserve;
    //! 移動
    std::weak_ptr<class PlayerMoveComponent> _move_com;
    //! 武器
    std::weak_ptr<class PlayerOmniWrenchComponent> _weapon_com;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    PlayerMeleeAttackTwoComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    PlayerMeleeAttackTwoComponent(const PlayerMeleeAttackTwoComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PlayerMeleeAttackTwoComponent();
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
    virtual std::shared_ptr<my::Component> Clone(void) override;
    /// <summary>
    /// 開始
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功</returns>
    virtual bool Start(void) override;
    /// <summary>
    /// 終了
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功</returns>
    virtual bool End(void) override;
};
}
#endif // !MY_PLAYER_MELEE_ATTACK_TWO_COMPONENT_H