#ifndef STATE_AI_COMBAT_STATE_H
#define STATE_AI_COMBAT_STATE_H


#include "My/Core/State.h"

#include <memory>

#include "AIState.h"


namespace state {
class AICombatState : public state::AIState {
    using super = state::AIState;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    AICombatState();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~AICombatState();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual const char* GetName(void) const override;
};
}
#endif // !STATE_AI_COMBAT_STATE_H