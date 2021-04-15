#ifndef STATE_ENEMY_MOTION_STATE_H
#define STATE_ENEMY_MOTION_STATE_H


#include "My/Core/State.h"

#include <memory>

#include <Mof.h>

#include "../Actor.h"
#include "../Actor/Character/Enemy.h"
#include "../Component/MotionComponent.h"
#include "../Component/MotionStateComponent.h"


namespace state {
class EnemyMotionState : public my::State {
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
    bool ChangeMotion(my::Enemy::MotionType type);
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
    EnemyMotionState();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~EnemyMotionState();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    virtual void SetActor(const std::shared_ptr<my::Actor>& ptr);
};
}
#endif // !STATE_ENEMY_MOTION_STATE_H