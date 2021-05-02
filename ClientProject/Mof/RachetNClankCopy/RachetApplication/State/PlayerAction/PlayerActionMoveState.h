#ifndef STATE_PLAYER_ACTION_MOVE_STATE_H
#define STATE_PLAYER_ACTION_MOVE_STATE_H


#include "PlayerActionState.h"

#include "../../Component/Player/PlayerMoveComponent.h"


namespace state {
class PlayerActionMoveState : public state::PlayerActionState {
    using super = state::PlayerActionState;
private:
    //! �ړ�
    std::weak_ptr<my::PlayerMoveComponent> _move_com;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    PlayerActionMoveState();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~PlayerActionMoveState();
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
#endif // !STATE_PLAYER_ACTION_MOVE_STATE_H