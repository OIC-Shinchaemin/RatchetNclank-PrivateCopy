#ifndef STATE_ENEMY_ACTION_MOVE_STATE_H
#define STATE_ENEMY_ACTION_MOVE_STATE_H


#include "EnemyActionState.h"

#include "../Component/Enemy/EnemyIdleComponent.h"
#include "../Component/Enemy/EnemyMoveComponent.h"
#include "../Component/Enemy/EnemyAttackComponent.h"


namespace state {
class EnemyActionMoveState : public state::EnemyActionState {
    using super = state::EnemyActionState;
private:
    //! �ҋ@
    std::weak_ptr<my::EnemyIdleComponent> _idle_com;
    //! �ړ�
    std::weak_ptr<my::EnemyMoveComponent> _move_com;
    //! �U��
    std::weak_ptr<my::EnemyAttackComponent> _attack_com;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    EnemyActionMoveState();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~EnemyActionMoveState();
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
#endif // !STATE_ENEMY_ACTION_MOVE_STATE_H