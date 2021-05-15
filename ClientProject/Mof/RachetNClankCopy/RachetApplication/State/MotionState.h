#ifndef STATE_MOTION_STATE_H
#define STATE_MOTION_STATE_H


#include "My/Core/State.h"

#include <memory>

#include <Mof.h>

//#include "PlayerMotionStateDefine.h"
#include "../Actor/Character/Player.h"
#include "../Component/MotionComponent.h"


namespace state {
class MotionState : public my::State {
private:
    //! �A�j���[�V�������x
    float _motion_speed;
    //! �A�j���[�V�������[�v
    bool _motion_loop;
    //! �A�j���[�V�����t���O
    bool _motion_same;
    //! ���[�V����
    std::weak_ptr<my::MotionComponent> _motion_com;
    /// <summary>
    /// �ύX
    /// </summary>
    /// <param name="type"></param>
    /// <returns></returns>
    bool ChangeMotion(my::Player::MotionType type);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    MotionState();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~MotionState();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    virtual void SetActor(const std::shared_ptr<my::Actor>& ptr);
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
#endif // !STATE_PLAYER_MOTION_STATE_H