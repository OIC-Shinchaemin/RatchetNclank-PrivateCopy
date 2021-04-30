#ifndef STATE_PLAYER_ACTION_STATE_H
#define STATE_PLAYER_ACTION_STATE_H


#include "My/Core/State.h"

#include <memory>

#include <Mof.h>

#include "PlayerActionStateDefine.h"
#include "../../Actor.h"
#include "../../Component/Player/PlayerStateComponent.h"


namespace state {
class PlayerActionState : public my::State {
private:
    //! �A�N�^�[
    std::weak_ptr<my::Actor> _actor;
    //! ���
    std::weak_ptr<my::PlayerStateComponent> _state_com;
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
    PlayerActionState();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~PlayerActionState();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    virtual void SetActor(const std::shared_ptr<my::Actor>& ptr);
};
}
#endif // !STATE_PLAYER_ACTION_STATE_H