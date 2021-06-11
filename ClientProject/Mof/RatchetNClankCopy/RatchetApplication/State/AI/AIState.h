#ifndef STATE_AI_STATE_H
#define STATE_AI_STATE_H


#include "Base/Core/State.h"

#include <memory>
#include <string>

#include "../../Actor.h"
#include "../../Behaviour/Executor/INodeExecutor.h"


namespace state {
class AIState : public base::core::State {
    using super = state::AIState;
protected:
    //! �ʒm
    std::weak_ptr<ratchet::Actor> _actor;
    //! �r�w�C�r�A���s
    behaviour::NodeExecutorPtr _behaviour_executor;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::Actor> GetActor(void) const;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    AIState();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~AIState();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    virtual void SetActor(const std::shared_ptr<ratchet::Actor>& ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="path"></param>
    void GenerateBehaviourExecutor(const std::string& path);
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
#ifdef _DEBUG
    /// <summary>
    /// �f�o�b�O
    /// </summary>
    /// <param name=""></param>
    virtual void DebugRender(void) override;
#endif // _DEBUG
};
}
#endif // !STATE_AI_STATE_H