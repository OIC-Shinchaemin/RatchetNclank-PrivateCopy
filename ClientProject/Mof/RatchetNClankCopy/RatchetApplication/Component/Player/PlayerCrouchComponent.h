#ifndef RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_CROUCH_COMPONENT_H
#define RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_CROUCH_COMPONENT_H


#include "PlayerActionComponent.h"

#include <functional>
#include <memory>
#include <string_view>
#include <vector>

#include "Base/Core/Timer.h"


namespace ratchet {
namespace component {
namespace player {
namespace action {
class PlayerCrouchComponent : public ::ratchet::component::player::action::PlayerActionComponent {
    using super = ::ratchet::component::player::action::PlayerActionComponent;
    using This = ::ratchet::component::player::action::PlayerCrouchComponent;
    struct InputInfo {
        Mof::CVector2 in;
        float move_angle = 0.0f;
        bool move_flag = false;

        void Reset(void) {
            in.x = 0.0f;
            in.y = 0.0f;
            move_angle = 0.0f;
            move_flag = false;
        }
    };
private:
    struct Transition {
        std::string_view state;
        std::function<bool(void)> condition;
        Transition(std::string_view name, std::function<bool(void)> lambda) :
            state(name), condition(lambda) {
        }
    };

   //! 遷移
   //std::vector<Transition> _transition_pairs;
   //! 回転速度
    float _angular_speed;
    //! ラジアン
    float _ideal_angle;
    //! 入力情報
    This::InputInfo _input_info;
    //! 遷移受付時間
    base::core::Timer _reception_timer;
    //! 遷移受付時間
    float _reception_time;
    //! カメラ
    std::weak_ptr<class PlayerMoveComponent> _move_com;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    PlayerCrouchComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    PlayerCrouchComponent(const PlayerCrouchComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PlayerCrouchComponent();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="speed"></param>
    void SetAngularSpeed(float speed);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="radian"></param>
    void SetIdealAngle(float radian);
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
}
}
}
#endif // !RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_CROUCH_COMPONENT_H