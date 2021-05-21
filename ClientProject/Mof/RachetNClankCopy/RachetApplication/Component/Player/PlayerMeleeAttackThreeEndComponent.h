#ifndef MY_PLAYER_MELEE_ATTACK_THREE_END_COMPONENT_H
#define MY_PLAYER_MELEE_ATTACK_THREE_END_COMPONENT_H


#include "PlayerActionComponent.h"


namespace my {
class PlayerMeleeAttackThreeEndComponent : public my::PlayerActionComponent {
    using super = my::PlayerActionComponent;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    PlayerMeleeAttackThreeEndComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    PlayerMeleeAttackThreeEndComponent(const PlayerMeleeAttackThreeEndComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PlayerMeleeAttackThreeEndComponent();
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
    /// 更新
    /// </summary>
    /// <param name="delta_time">時間</param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
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
};
}
#endif // !MY_PLAYER_MELEE_ATTACK_THREE_END_COMPONENT_H