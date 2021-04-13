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
    //! �A�j���[�V�������x
    float _motion_speed;
    //! �A�j���[�V�������[�v
    bool _motion_loop;
    //! �A�j���[�V�����t���O
    bool _motion_same;
    //! ���[�V����
    std::weak_ptr<my::MotionComponent> _motion_com;
    //! ���
    std::weak_ptr<my::MotionStateComponent> _motion_state_com;

    //! ���x
    my::Velocity* _velocity;
    //! ���x
    std::weak_ptr<my::Attack> _attack;
    /// <summary>
    /// �ύX
    /// </summary>
    /// <param name="type"></param>
    /// <returns></returns>
    bool ChangeMotion(my::Enemy::MotionType type);
    /// <summary>
    /// �ύX
    /// </summary>
    /// <param name="next"></param>
    /// <returns></returns>
    bool ChangeState(const char* next) const;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    EnemyMotionState();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~EnemyMotionState();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetEnemy(const std::shared_ptr<my::Enemy>& ptr);
};
}
#endif // !STATE_ENEMY_MOTION_STATE_H