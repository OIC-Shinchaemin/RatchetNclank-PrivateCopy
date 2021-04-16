#ifndef STATE_AI_STATE_H
#define STATE_AI_STATE_H


#include "My/Core/State.h"

#include <memory>
#include <string>

#include "../Actor.h"
#include "../Actor/Character/Enemy.h"
#include "../Behaviour/Executor/INodeExecutor.h"
#include "../Factory/BehaviourExecutorFactory.h"


namespace state {
class AIState : public my::State {
    using super = state::AIState;
protected:
    //! �ʒm
    std::weak_ptr<my::Enemy> _enemy;
    //! �r�w�C�r�A���s
    behaviour::NodeExecutorPtr _behaviour_executor;
    //! �p�X
    std::string _behaviour_path;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<my::Enemy> GetEnemy(void) const;
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
    virtual void SetActor(const std::shared_ptr<my::Actor>& ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void GenerateBehaviourExecutor(void);
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
    /// <summary>
    /// �f�o�b�O
    /// </summary>
    /// <param name=""></param>
    virtual void DebugRender(void) override;
};
}
#endif // !STATE_AI_STATE_H