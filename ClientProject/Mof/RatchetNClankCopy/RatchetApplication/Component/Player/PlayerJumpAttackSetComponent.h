#ifndef RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_JUMP_ATTACK_SET_COMPONENT_H
#define RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_JUMP_ATTACK_SET_COMPONENT_H


#include "PlayerActionComponent.h"

#include <memory>


namespace ratchet {
namespace component {
namespace player {
class PlayerOmniWrenchComponent;
namespace action {
class PlayerJumpAttackSetComponent : public ratchet::component::player::action::PlayerActionComponent {
    using super = ratchet::component::player::action::PlayerActionComponent;
private:
    //! 速さ
    float _up_speed;
    //! 武器
    std::weak_ptr<ratchet::component::player::PlayerOmniWrenchComponent> _weapon_com;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    PlayerJumpAttackSetComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    PlayerJumpAttackSetComponent(const PlayerJumpAttackSetComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PlayerJumpAttackSetComponent();
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
    virtual std::shared_ptr<ratchet::component::Component> Clone(void) override;
    /// <summary>
    /// 開始
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功</returns>
    virtual bool Start(void) override;
};
}
}
}
}
#endif // !RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_JUMP_ATTACK_SET_COMPONENT_H