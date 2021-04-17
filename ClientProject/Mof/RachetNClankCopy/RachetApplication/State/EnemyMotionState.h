#ifndef STATE_ENEMY_MOTION_STATE_H
#define STATE_ENEMY_MOTION_STATE_H


#include "My/Core/State.h"

#include <memory>

#include <Mof.h>

#include "My/Core/Observable.h"
#include "My/Core/Observer.h"
#include "../MotionNames.h"
#include "../Component/MotionComponent.h"
#include "../Component/MotionStateComponent.h"
#include "../Character/Enemy.h"
#include "../Velocity.h"
#include "../Attack.h"


namespace state {
/*
template <typename Type>
class TransitionRules {
    using Condition = std::function<bool(Type&)>;
private:
    Condition _condition;
public:
    TransitionRules(Condition) :
        _condition() {
    }
    bool operator()(Type& instance) const {
        return _condition(instance);
    }
};
*/
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

    //! 速度
    my::Velocity* _velocity;
    //! 速度
    std::weak_ptr<my::Attack> _attack;
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
    void SetEnemy(const std::shared_ptr<my::Enemy>& ptr);
};
}
#endif // !STATE_ENEMY_MOTION_STATE_H