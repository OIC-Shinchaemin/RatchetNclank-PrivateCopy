#ifndef RATCHET_STATE_AI_AI_PATROL_STATE_H
#define RATCHET_STATE_AI_AI_PATROL_STATE_H


#include "AIState.h"


namespace ratchet {

namespace state {
namespace ai {
class AIPatrolState : public ratchet::state::ai::AIState {
    using super = ratchet::state::ai::AIState;
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
}
}
#endif // !RATCHET_STATE_AI_AI_PATROL_STATE_H