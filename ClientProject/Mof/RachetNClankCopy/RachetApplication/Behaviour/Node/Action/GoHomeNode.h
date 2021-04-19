#ifndef BEHAVIOUR_GO_HOME_NODE_H
#define BEHAVIOUR_GO_HOME_NODE_H


#include "../ActionNode.h"

#include "../Component/Enemy/EnemyStateComponent.h"
#include "../Component/Enemy/EnemyMoveComponent.h"
#include "../Component/Enemy/EnemyAttackComponent.h"


namespace behaviour {
class GoHomeNode : public behaviour::ActionNodeBase {
    using super = behaviour::ActionNodeBase;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    GoHomeNode() :
        super("GoHomeNode") {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~GoHomeNode() = default;
    /// <summary>
    /// �m�[�h�̎��s
    /// </summary>
    /// <param name="actor">���s�A�N�^�[</param>
    /// <returns>true:���s�̐���</returns>
    /// <returns>false:���s�̎��s</returns>
    virtual bool Execute(std::any ptr) override {
        auto actor = std::any_cast<std::shared_ptr<my::Actor>>(ptr);

        auto state_com = actor->GetComponent<my::EnemyStateComponent>();
        state_com->ChangeState("EnemyActionGoHomeState");

        float distance = Mof::CVector3Utilities::Distance(actor->GetInitialPosition(), actor->GetPosition());
        if (distance > 2.0f) {
            return false;
        } // if
        return true;
    }
};
}
#endif // !BEHAVIOUR_GO_HOME_NODE_H