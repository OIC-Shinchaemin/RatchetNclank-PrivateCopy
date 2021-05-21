#ifndef MY_PLAYER_THROW_ATTACK_COMPONENT_H
#define MY_PLAYER_THROW_ATTACK_COMPONENT_H


#include "PlayerActionComponent.h"

#include <memory>


namespace my {
class PlayerThrowAttackComponent : public my::PlayerActionComponent {
    using super = my::PlayerActionComponent;
private:
    //! 武器
    std::weak_ptr<class PlayerWeaponComponent> _weapon_com;
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