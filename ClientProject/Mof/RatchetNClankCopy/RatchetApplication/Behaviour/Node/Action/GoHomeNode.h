#ifndef RATCHET_BEHAVIOUR_GO_HOME_NODE_H
#define RATCHET_BEHAVIOUR_GO_HOME_NODE_H


#include "../ActionNode.h"

#include "../../Executor/Action/GoHomeNodeExecutor.h"
#include "../../../State/EnemyActionStateDefine.h"


namespace ratchet {  namespace behaviour {
class GoHomeNode : public ratchet::behaviour::ActionNodeBase {
    using super = ratchet::behaviour::ActionNodeBase;
    using Executor = ratchet::behaviour::GoHomeNodeExecutor;
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
    /// �쐬
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual ratchet::behaviour::NodeExecutorPtr CreateExecutor(void) const {
        auto ptr = std::const_pointer_cast<ratchet::behaviour::Node>(super::shared_from_this());
        return std::make_shared<Executor>(ptr);
    }
    /// <summary>
    /// �m�[�h�̎��s
    /// </summary>
    /// <param name="node_args">���s����</param>
    /// <returns>true:���s�̐���</returns>
    /// <returns>false:���s�̎��s</returns>
    virtual bool Execute(std::any node_args) override {
        auto args = std::any_cast<Executor::NodeArgs>(node_args);

        if (args.state_com.lock()->CanTransition(ratchet::state::EnemyActionStateType::kEnemyActionGoHomeState)) {
            args.state_com.lock()->ChangeState(ratchet::state::EnemyActionStateType::kEnemyActionGoHomeState);
        } // if

        auto pos = args.actor.lock()->GetPosition();
        auto init_pos = args.actor.lock()->GetInitialPosition();
        float distance = Mof::CVector3Utilities::Distance(pos, init_pos);
        if (distance < args.type_com.lock()->GetHomeDistance()) {
            return true;
        } // if
        return false;
    }
};
}
}
#endif // !RATCHET_BEHAVIOUR_GO_HOME_NODE_H