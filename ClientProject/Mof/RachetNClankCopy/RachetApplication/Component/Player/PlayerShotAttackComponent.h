#ifndef RACHET_PLAYER_SHOT_ATTACK_COMPONENT_H
#define RACHET_PLAYER_SHOT_ATTACK_COMPONENT_H


#include "PlayerActionComponent.h"

#include <memory>

#include "../../Actor/Weapon/Mechanical.h"


namespace rachet {
class PlayerShotAttackComponent : public rachet::PlayerActionComponent {
    using super = rachet::PlayerActionComponent;
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
    //! 武器
    std::weak_ptr<rachet::Mechanical> _weapon;
    //! 入力情報
    rachet::PlayerShotAttackComponent::InputInfo _input_info;
    //! 移動
    std::weak_ptr<class PlayerMoveComponent> _move_com;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    PlayerShotAttackComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    PlayerShotAttackComponent(const PlayerShotAttackComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PlayerShotAttackComponent();
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
    virtual std::shared_ptr<rachet::Component> Clone(void) override;
    /// <summary>
    /// 開始
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功</returns>
    virtual bool Start(void) override;
};
}
#endif // !RACHET_PLAYER_SHOT_ATTACK_COMPONENT_H