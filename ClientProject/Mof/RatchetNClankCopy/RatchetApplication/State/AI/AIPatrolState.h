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
    /// コンストラクタ
    /// </summary>
    AIPatrolState();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~AIPatrolState();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual const char* GetName(void) const override;
};
}
}
}
#endif // !RATCHET_STATE_AI_AI_PATROL_STATE_H