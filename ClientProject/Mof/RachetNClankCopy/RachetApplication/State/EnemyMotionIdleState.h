#ifndef STATE_ENEMY_MOTION_IDLE_STATE_H
#define STATE_ENEMY_MOTION_IDLE_STATE_H


#include "EnemyMotionState.h"


namespace state {
class EnemyMotionIdleState : public state::EnemyMotionState {
    using super = state::EnemyMotionState;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    EnemyMotionIdleState();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~EnemyMotionIdleState();
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual const char* GetName(void) const override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    virtual void Update(float delta_time) override;
    /// <summary>
    /// �J�n
    /// </summary>
    /// <param name=""></param>
    virtual void Enter(void) override;
    /// <summary>
    /// �I��
    /// </summary>
    /// <param name=""></param>
    virtual void Exit(void) override;
};
}
#endif // !STATE_ENEMY_MOTION_IDLE_STATE_H