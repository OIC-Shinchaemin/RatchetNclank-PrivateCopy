#ifndef BEHAVIOUR_GO_HOME_NODE_H
#define BEHAVIOUR_GO_HOME_NODE_H


#include "Node.h"

#include "../Executor/ActionNodeExecutor.h"


namespace behaviour {
template<typename Actor>
class GoHomeNode : public behaviour::ActionNodeBase<Actor> {
    using super = behaviour::ActionNodeBase<Actor>;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    GoHomeNode() :
        super() {
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
    virtual bool Execute(Actor& actor) override {
        actor->ChaseTo(actor->GetInitPosition(), 0.3f, 1.0f);

        if (actor->GetDistanceFromInitPosition() > 2.0f) {
            return false;
        } // if
        return true;
    }
};
}
#endif // !BEHAVIOUR_GO_HOME_NODE_H