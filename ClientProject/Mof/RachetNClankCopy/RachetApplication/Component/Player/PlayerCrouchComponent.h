#ifndef MY_PLAYER_CROUCH_COMPONENT_H
#define MY_PLAYER_CROUCH_COMPONENT_H


#include "PlayerActionComponent.h"

#include <functional>
#include <memory>
#include <string_view>
#include <vector>


namespace my {
class PlayerCrouchComponent : public my::PlayerActionComponent {
    using super = my::PlayerActionComponent;
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
    /// 加速
    /// </summary>
    /// <param name="move_speed"></param>
    /// <param name="angular_speed"></param>
    /// <param name="ideal_angle"></param>
    /// <returns>実行</returns>
    //bool Move(float move_speed, float angular_speed, float ideal_angle);
    /// <summary>
    /// 獲得
    /// </summary>
    /// <param name="stick">出力</param>
    /// <param name="move_angle">出力</param>
    /// <returns></returns>
    //bool AquireInputData(Mof::CVector2& stick, float& move_angle);
};
}
#endif // !MY_PLAYER_CROUCH_COMPONENT_H