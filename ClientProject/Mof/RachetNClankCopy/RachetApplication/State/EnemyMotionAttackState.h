#ifndef STATE_ENEMY_MOTION_ATTACK_STATE_H
#define STATE_ENEMY_MOTION_ATTACK_STATE_H


#include "EnemyMotionState.h"

#include <memory>

#include "../Component/AttackComponent.h"


namespace state {
class EnemyMotionAttackState : public state::EnemyMotionState {
    using super = state::EnemyMotionState;
private:
    //! �U��
    std::weak_ptr<my::AttackComponent> _attack_com;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    EnemyMotionAttackState();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~EnemyMotionAttackState();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    virtual void SetEnemy(const std::shared_ptr<my::Enemy>& ptr) override;
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
#endif // !STATE_ENEMY_MOTION_ATTACK_STATE_H