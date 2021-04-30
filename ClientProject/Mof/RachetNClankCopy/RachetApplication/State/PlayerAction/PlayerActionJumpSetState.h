#ifndef STATE_PLAYER_ACTION_JUMP_SET_STATE_H
#define STATE_PLAYER_ACTION_JUMP_SET_STATE_H


#include "PlayerActionState.h"

#include "../../Component/Player/PlayerJumpSetComponent.h"


namespace state {
class PlayerActionJumpSetState : public state::PlayerActionState {
    using super = state::PlayerActionState;
private:
    //! �W�����v
    std::weak_ptr<my::PlayerJumpSetComponent> _jump_com;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    PlayerActionJumpSetState();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~PlayerActionJumpSetState();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    virtual void SetActor(const std::shared_ptr<my::Actor>& ptr) override;
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
#endif // !STATE_PLAYER_ACTION_JUMP_SET_STATE_H