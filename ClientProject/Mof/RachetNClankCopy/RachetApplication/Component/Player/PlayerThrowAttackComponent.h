#ifndef MY_PLAYER_THROW_ATTACK_COMPONENT_H
#define MY_PLAYER_THROW_ATTACK_COMPONENT_H


#include "../ActionComponent.h"

#include <memory>

#include "PlayerStateComponent.h"


namespace my {
class PlayerThrowAttackComponent : public my::ActionComponent {
    using super = my::ActionComponent;
private:
    //! 状態
    std::weak_ptr<class PlayerStateComponent> _state_com;
    //! モーション
    std::weak_ptr<class MotionComponent> _motion_com;
    //! モーション
    std::weak_ptr<class MotionStateComponent> _motion_state_com;
    //! 武器
    std::weak_ptr<class PlayerWeaponComponent> _weapon_com;
    /// <summary>
    /// 変更
    /// </summary>
    /// <param name="name"></param>
    void ChageState(const std::string& name);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    PlayerThrowAttackComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    PlayerThrowAttackComponent(const PlayerThrowAttackComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PlayerThrowAttackComponent();
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
#endif // !MY_PLAYER_THROW_ATTACK_COMPONENT_H