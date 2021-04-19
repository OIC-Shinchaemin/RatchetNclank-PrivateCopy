#ifndef BEHAVIOUR_LOOK_AROUND_NODE_H
#define BEHAVIOUR_LOOK_AROUND_NODE_H


#include "../ActionNode.h"

#include "../../../Component/AIStateComponent.h"
#include "../../../Component/Enemy/EnemyStateComponent.h"
#include "../../../Actor/Character/Enemy.h"


namespace behaviour {
class LookAroundNode : public behaviour::ActionNodeBase {
    using super = behaviour::ActionNodeBase;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    LookAroundNode() :
        super("LookAroundNode") {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~LookAroundNode() = default;
    /// <summary>
    /// �m�[�h�̎��s
    /// </summary>
    /// <param name="actor">���s�A�N�^�[</param>
    /// <returns>true:���s�̐���</returns>
    /// <returns>false:���s�̎��s</returns>
    virtual bool Execute(std::any ptr) override {
        auto actor = std::any_cast<std::shared_ptr<my::Actor>>(ptr);

        if (!std::dynamic_pointer_cast<my::Enemy>(actor)->GetTarget().expired()) {
            auto ai_state_com = actor->GetComponent<my::AIStateComponent>();
            ai_state_com->ChangeState("AICombatState");
            return true;
        } // if

        auto state_com = actor->GetComponent<my::EnemyStateComponent>();
        state_com->ChangeState("EnemyActionIdleState");
        return false;
    }
};
}
#endif // !BEHAVIOUR_LOOK_AROUND_NODE_H