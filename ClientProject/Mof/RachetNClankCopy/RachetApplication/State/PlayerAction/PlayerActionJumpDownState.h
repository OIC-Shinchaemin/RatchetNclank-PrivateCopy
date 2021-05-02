#ifndef STATE_PLAYER_ACTION_JUMP_DOWN_STATE_H
#define STATE_PLAYER_ACTION_JUMP_DOWN_STATE_H


#include "PlayerActionState.h"

#include "../../Component/Player/PlayerJumpDownComponent.h"


namespace state {
class PlayerActionJumpDownState : public state::PlayerActionState {
    using super = state::PlayerActionState;
private:
    //! �W�����v
    std::weak_ptr<my::PlayerJumpDownComponent> _jump_com;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    PlayerActionJumpDownState();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~PlayerActionJumpDownState();
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
#endif // !STATE_PLAYER_ACTION_JUMP_DOWN_STATE_H