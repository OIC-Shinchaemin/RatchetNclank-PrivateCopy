#ifndef STATE_PLAYER_ACTION_MELEE_ATTACK_TWO_END_STATE_H
#define STATE_PLAYER_ACTION_MELEE_ATTACK_TWO_END_STATE_H


#include "PlayerActionState.h"

#include "../../Component/Player/PlayerMeleeAttackTwoEndComponent.h"


namespace state {
class PlayerActionMeleeAttackTwoEndState : public state::PlayerActionState {
    using super = state::PlayerActionState;
private:
    //! �U��
    std::weak_ptr<my::PlayerMeleeAttackTwoEndComponent> _attack_com;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    PlayerActionMeleeAttackTwoEndState();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~PlayerActionMeleeAttackTwoEndState();
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
#endif // !STATE_PLAYER_ACTION_MELEE_ATTACK_TWO_END_STATE_H