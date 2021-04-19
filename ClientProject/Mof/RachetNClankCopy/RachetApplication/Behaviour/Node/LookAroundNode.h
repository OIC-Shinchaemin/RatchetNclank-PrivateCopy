#ifndef BEHAVIOUR_LOOK_AROUND_NODE_H
#define BEHAVIOUR_LOOK_AROUND_NODE_H


#include "Node.h"

#include "../Executor/ActionNodeExecutor.h"

#include "../../Component/AIStateComponent.h"
#include "../../Component/EnemyIdleComponent.h"



namespace behaviour {
template<typename Actor>
class LookAroundNode : public behaviour::ActionNodeBase<Actor> {
    using super = behaviour::ActionNodeBase<Actor>;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    LookAroundNode() :
        super() {
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
    virtual bool Execute(Actor& actor) override {
        if (actor->HasTarget()) {
            auto ai_state_com = actor->GetComponent<my::AIStateComponent>();
            ai_state_com->ChangeState("AICombatState");
            return true;
        } // if

        auto idle_com = actor->GetComponent<my::EnemyIdleComponent>();

        float tilt = 1.0f;
        Mof::CVector2 in = Mof::CVector2(tilt, 0.0f);

        auto angle_y = math::ToDegree(actor->GetRotate().y);

        in = math::Rotate(in.x, in.y, ut::GenerateRandomF(0.0f, math::kTwoPi));
        float angular_speed = 4.0f;

        idle_com->SetAngularSpeed(angular_speed);
        idle_com->SetIdealAngle(std::atan2(-in.y, in.x) - math::kHalfPi);
        idle_com->Start();
        return false;
    }
};
}
#endif // !BEHAVIOUR_LOOK_AROUND_NODE_H