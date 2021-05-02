#ifndef STATE_ENEMY_ACTION_STATE_H
#define STATE_ENEMY_ACTION_STATE_H


#include "My/Core/State.h"

#include <memory>

#include <Mof.h>

#include "EnemyActionStateDefine.h"
#include "../../Actor.h"
#include "../../Component/Enemy/EnemyStateComponent.h"


namespace state {
class EnemyActionState : public my::State {
private:
    //! �A�N�^�[
    std::weak_ptr<my::Actor> _actor;
    //! ���
    std::weak_ptr<my::EnemyStateComponent> _state_com;
protected:
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<my::Actor>GetActor(void) const;
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
    EnemyActionState();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~EnemyActionState();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    virtual void SetActor(const std::shared_ptr<my::Actor>& ptr);
};
}
#endif // !STATE_ENEMY_ACTION_STATE_H