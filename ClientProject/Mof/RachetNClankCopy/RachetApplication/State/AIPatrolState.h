#ifndef STATE_AI_PATROL_STATE_H
#define STATE_AI_PATROL_STATE_H


#include "My/Core/State.h"

#include <memory>

#include "AIState.h"


namespace state {
class AIPatrolState : public state::AIState {
    using super = state::AIState;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    AIPatrolState();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~AIPatrolState();
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual const char* GetName(void) const override;
};
}
#endif // !STATE_AI_PATROL_STATE_H