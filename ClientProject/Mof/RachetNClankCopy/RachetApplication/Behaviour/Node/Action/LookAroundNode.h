#ifndef BEHAVIOUR_LOOK_AROUND_NODE_H
#define BEHAVIOUR_LOOK_AROUND_NODE_H


#include "../ActionNode.h"

#include "../../../Component/AIStateComponent.h"
#include "../../../Component/Enemy/EnemyIdleComponent.h"
#include "../../../Component/Enemy/EnemyMoveComponent.h"


namespace behaviour {
template<typename Actor>
class LookAroundNode : public behaviour::ActionNodeBase<Actor> {
    using super = behaviour::ActionNodeBase<Actor>;
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
    virtual bool Execute(Actor& actor) override {
        if (!actor->GetTarget().expired()) {
            auto ai_state_com = actor->GetComponent<my::AIStateComponent>();
            ai_state_com->ChangeState("AICombatState");
            return true;
        } // if
        float tilt = 1.0f;
        Mof::CVector2 in = Mof::CVector2(tilt, 0.0f);

        auto angle_y = math::ToDegree(actor->GetRotate().y);

        in = math::Rotate(in.x, in.y, ut::GenerateRandomF(0.0f, math::kTwoPi));
        float angular_speed = 4.0f;

        auto idle_com = actor->GetComponent<my::EnemyIdleComponent>();
        idle_com->SetAngularSpeed(angular_speed);
        idle_com->SetIdealAngle(std::atan2(-in.y, in.x) - math::kHalfPi);
        idle_com->Start();
        auto move_com = actor->GetComponent<my::EnemyMoveComponent>();
        move_com->SetMoveSpeed(0.0f);
        move_com->SetAngularSpeed(0.0f);
        move_com->End();
        return false;
    }
};
}
#endif // !BEHAVIOUR_LOOK_AROUND_NODE_H