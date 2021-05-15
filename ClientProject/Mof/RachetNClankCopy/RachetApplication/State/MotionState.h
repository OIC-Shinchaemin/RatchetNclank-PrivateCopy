#ifndef STATE_MOTION_STATE_H
#define STATE_MOTION_STATE_H


#include "My/Core/State.h"

#include <memory>

#include <Mof.h>

//#include "PlayerMotionStateDefine.h"
#include "../Actor/Character/Player.h"
#include "../Component/MotionComponent.h"


namespace state {
class MotionState : public my::State {
private:
    //! アニメーション速度
    float _motion_speed;
    //! アニメーションループ
    bool _motion_loop;
    //! アニメーションフラグ
    bool _motion_same;
    //! モーション
    std::weak_ptr<my::MotionComponent> _motion_com;
    /// <summary>
    /// 変更
    /// </summary>
    /// <param name="type"></param>
    /// <returns></returns>
    bool ChangeMotion(my::Player::MotionType type);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    MotionState();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~MotionState();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    virtual void SetActor(const std::shared_ptr<my::Actor>& ptr);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual const char* GetName(void) const override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    virtual void Update(float delta_time) override;
    /// <summary>
    /// 開始
    /// </summary>
    /// <param name=""></param>
    virtual void Enter(void) override;
    /// <summary>
    /// 終了
    /// </summary>
    /// <param name=""></param>
    virtual void Exit(void) override;
};
}
#endif // !STATE_PLAYER_MOTION_STATE_H