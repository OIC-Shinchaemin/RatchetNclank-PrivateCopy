#ifndef BEHAVIOUR_CHANGE_PATROL_NODE_H
#define BEHAVIOUR_CHANGE_PATROL_NODE_H


#include "../ActionNode.h"

#include "../../../Component/AIStateComponent.h"


namespace behaviour {
class ChangePatrolNode : public behaviour::ActionNodeBase {
    using super = behaviour::ActionNodeBase;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ChangePatrolNode() :
        super("ChangePatrolNode") {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~ChangePatrolNode() = default;
    /// <summary>
    /// �m�[�h�̎��s
    /// </summary>
    /// <param name="actor">���s�A�N�^�[</param>
    /// <returns>true:���s�̐���</returns>
    /// <returns>false:���s�̎��s</returns>
    virtual bool Execute(std::any ptr) override {
        auto actor = std::any_cast<std::shared_ptr<my::Actor>>(ptr);

        // can transition state
        if (1) {
        } // if
        auto ai_state_com = actor->GetComponent<my::AIStateComponent>();
        ai_state_com->ChangeState("AIPatrolState");
        return true;
    }
};
}
#endif // !BEHAVIOUR_CHANGE_PATROL_NODE_H