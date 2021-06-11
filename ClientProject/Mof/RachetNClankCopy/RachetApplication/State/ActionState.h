#ifndef RACHET_STATE_ACTION_STATE_H
#define RACHET_STATE_ACTION_STATE_H


#include "Base/Core/State.h"

#include <memory>

#include "../Component/ActionComponent.h"


namespace state {
class ActionState : public base::core::State {
private:
    //! �A�N�V����
    std::weak_ptr<rachet::ActionComponent> _action_com;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ActionState();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~ActionState();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    virtual void SetActionComponent(const std::shared_ptr<rachet::ActionComponent>& ptr);
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
#endif // !RACHET_STATE_PLAYER_ACTION_STATE_H