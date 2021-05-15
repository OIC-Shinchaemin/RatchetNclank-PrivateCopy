#ifndef STATE_MOTION_STATE_H
#define STATE_MOTION_STATE_H


#include "My/Core/State.h"

#include <memory>
#include <string>

#include "../Component/MotionComponent.h"


namespace state {
class MotionState : public my::State {
public:
    struct Param {
        //! ���O
        const char* state_name;
        //! �^�C�v
        int motion_type;
        //! �A�j���[�V�������x
        float motion_speed;
        //! �A�j���[�V�������[�v
        bool motion_loop;
        //! �A�j���[�V�����t���O
        bool motion_same;

        Param() :
            state_name(),
            motion_type(),
            motion_speed(),
            motion_loop(),
            motion_same() {
        }
        template<typename Enum>
        Param(const std::string& name, Enum type, float speed = 1.0f, bool loop = true, bool same = true) :
            state_name(name),
            motion_type(type),
            motion_speed(speed),
            motion_loop(loop),
            motion_same(same) {
        }
    };
private:
    //! �p�����[�^
    Param _param;
    //! ���[�V����
    std::weak_ptr<my::MotionComponent> _motion_com;
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
    /// �Z�b�^�[
    /// </summary>
    /// <param name="param"></param>
    void SetParam(const state::MotionState::Param& param);
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