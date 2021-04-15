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
    virtual void SetActor(const std::shared_ptr<my::Actor>& ptr);
};
}
#endif // !STATE_ENEMY_MOTION_STATE_H