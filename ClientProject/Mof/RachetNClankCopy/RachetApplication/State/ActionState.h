#ifndef STATE_ACTION_STATE_H
#define STATE_ACTION_STATE_H


#include "My/Core/State.h"

#include <memory>

#include "../Actor.h"
#include "../Component/ActionComponent.h"
#include "../Component/ActionStateComponent.h"


namespace state {
class ActionState : public my::State {
private:
    //! �A�N�^�[
    std::weak_ptr<my::Actor> _actor;
    //! �A�N�V����
    std::weak_ptr<my::ActionComponent> _action_com;
protected:
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<my::Actor>GetActor(void) const;
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
    virtual void SetActor(const std::shared_ptr<my::Actor>& ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    virtual void SetActionComponent(const std::shared_ptr<my::ActionComponent>& ptr);
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
#endif // !STATE_PLAYER_ACTION_STATE_H