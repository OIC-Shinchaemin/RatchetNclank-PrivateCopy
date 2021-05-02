#ifndef STATE_ENEMY_ACTION_DAMAGE_STATE_H
#define STATE_ENEMY_ACTION_DAMAGE_STATE_H


#include "EnemyActionState.h"

#include "../../Component/Enemy/EnemyDamageComponent.h"
#include "../../Component/Enemy/EnemyMoveComponent.h"


namespace state {
class EnemyActionDamageState : public state::EnemyActionState {
    using super = state::EnemyActionState;
private:
    //! �ҋ@
    std::weak_ptr<my::EnemyDamageComponent> _damage_com;
    //! �ړ�
    std::weak_ptr<my::EnemyMoveComponent> _move_com;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    EnemyActionDamageState();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~EnemyActionDamageState();
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
#endif // !STATE_ENEMY_ACTION_DAMAGE_STATE_H