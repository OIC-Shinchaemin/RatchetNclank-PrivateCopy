#ifndef RACHET_PLAYER_JUMP_SET_COMPONENT_H
#define RACHET_PLAYER_JUMP_SET_COMPONENT_H


#include "PlayerActionComponent.h"

#include <memory>


namespace rachet {
class PlayerJumpSetComponent : public rachet::PlayerActionComponent {
    using super = rachet::PlayerActionComponent;
    using This = rachet::PlayerJumpSetComponent;
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
    //! ジャンプ
    float _jump_speed;
    //! ジャンプ
    float _jump_speed_first;
    //! ジャンプ
    float _jump_speed_increase;
    //! 入力情報
    This::InputInfo _input_info;
    //! 移動
    std::weak_ptr<class PlayerMoveComponent> _move_com;
    //! 移動
    std::weak_ptr<class PlayerJumpUpComponent> _jump_com;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    PlayerJumpSetComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    PlayerJumpSetComponent(const PlayerJumpSetComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PlayerJumpSetComponent();
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
    virtual std::shared_ptr<rachet::Component> Clone(void) override;
    /// <summary>
    /// 開始
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功</returns>
    virtual bool Start(void) override;
};
}
#endif // !RACHET_PLAYER_JUMP_SET_COMPONENT_H