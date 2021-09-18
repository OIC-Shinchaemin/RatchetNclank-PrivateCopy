#ifndef RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_IDLE_COMPONENT_H
#define RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_IDLE_COMPONENT_H


#include "PlayerActionComponent.h"


namespace ratchet::component::player { class PlayerComponent; }
namespace ratchet::component::player::action {
class PlayerIdleComponent : 
    public ::ratchet::component::player::action::PlayerActionComponent {
    using super = ::ratchet::component::player::action::PlayerActionComponent;
private:
    //! 型機能
    std::weak_ptr<ratchet::component::player::PlayerComponent> _type_com;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    PlayerIdleComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    PlayerIdleComponent(const PlayerIdleComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PlayerIdleComponent();
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
#endif // !RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_IDLE_COMPONENT_H