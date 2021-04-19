#ifndef STATE_PLAYER_MOTION_IDLE_STATE_H
#define STATE_PLAYER_MOTION_IDLE_STATE_H


#include "PlayerMotionState.h"


namespace state {
class PlayerMotionIdleState : public state::PlayerMotionState {
    using super = state::PlayerMotionState;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    PlayerMotionIdleState();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~PlayerMotionIdleState();
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
#endif // !STATE_PLAYER_MOTION_IDLE_STATE_H