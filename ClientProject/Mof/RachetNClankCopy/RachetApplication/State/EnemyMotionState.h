#ifndef STATE_ENEMY_MOTION_STATE_H
#define STATE_ENEMY_MOTION_STATE_H


#include "My/Core/State.h"

#include <memory>

#include <Mof.h>

#include "My/Core/Observable.h"
#include "My/Core/Observer.h"
#include "../MotionNames.h"
#include "../Character/Enemy.h"
#include "../Velocity.h"


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
    //! アニメーションデータ
    Mof::LPMeshMotionController _motion;
    //! 名前
    std::weak_ptr<my::MotionNames> _motion_names;
    //! 通知
    std::weak_ptr<my::Enemy> _enemy;
    //! 速度
    my::Velocity* _velocity;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool IsEndMotion(void) const;
    /// <summary>
    /// 変更
    /// </summary>
    /// <param name="type"></param>
    /// <returns></returns>
    template<typename Enum>
    bool ChangeMotion(Enum type) {
        if (auto motion_names = _motion_names.lock(); motion_names && _motion) {
            return _motion->ChangeMotionByName(
                motion_names->At(type),
                _motion_speed, _motion_loop, _motion_same);
        } // if
        return false;
    }
    bool ChangeState(const char* next) {
        if (auto ptr = _enemy.lock()) {
            ptr->ChangeMotionState(next);
            return true;
        } // if
        return false;
    }
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
    void SetLPMeshMotionController(Mof::LPMeshMotionController ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetMotionNames(const std::weak_ptr<my::MotionNames>& ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetEnemy(const std::shared_ptr<my::Enemy>& ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetVelocity(my::Velocity* ptr);
};
}
#endif // !STATE_ENEMY_MOTION_STATE_H