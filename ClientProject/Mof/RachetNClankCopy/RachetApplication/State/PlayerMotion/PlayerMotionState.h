#ifndef STATE_PLAYER_MOTION_STATE_H
#define STATE_PLAYER_MOTION_STATE_H


#include "My/Core/State.h"

#include <memory>

#include <Mof.h>

#include "../../MotionNames.h"
#include "../../Actor/Character/Player.h"
#include "../../Component/MotionComponent.h"
#include "../../Component/MotionStateComponent.h"


namespace state {
class PlayerMotionState : public my::State {
protected:
    //! アニメーション速度
    float _motion_speed;
    //! アニメーションループ
    bool _motion_loop;
    //! アニメーションフラグ
    bool _motion_same;
    //! モーション
    std::weak_ptr<my::MotionComponent> _motion_com;
    //! 状態
    std::weak_ptr<my::MotionStateComponent> _motion_state_com;
    /// <summary>
    /// 変更
    /// </summary>
    /// <param name="type"></param>
    /// <returns></returns>
    bool ChangeMotion(my::Player::MotionType type);
    /// <summary>
    /// 変更
    /// </summary>
    /// <param name="next"></param>
    /// <returns></returns>
    bool ChangeState(const char* next) const;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    PlayerMotionState();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PlayerMotionState();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    virtual void SetActor(const std::shared_ptr<my::Actor>& ptr);
};
}
#endif // !STATE_PLAYER_MOTION_STATE_H