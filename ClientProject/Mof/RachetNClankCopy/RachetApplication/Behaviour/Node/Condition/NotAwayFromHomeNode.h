#ifndef BEHAVIOUR_NOT_AWAY_FROM_HOME_NODE_H
#define BEHAVIOUR_NOT_AWAY_FROM_HOME_NODE_H


#include "../ConditionalNode.h"


namespace behaviour {
template<typename Actor>
class NotAwayFromHomeNode: public behaviour::ConditionalNodeBase<Actor> {
    using super = behaviour::ConditionalNodeBase<Actor>;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    NotAwayFromHomeNode() :
        super("NotAwayFromHomeNode") {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~NotAwayFromHomeNode() = default;
    /// <summary>
    /// �m�[�h�̎��s����
    /// </summary>
    /// <param name="actor">���s�A�N�^�[</param>
    /// <returns>Succeeded:���s�̐���</returns>
    /// <returns>Failed:���s�̎��s</returns>
    virtual bool Execute(Actor& actor) override {
        return Mof::CVector3Utilities::Distance(actor->GetInitialPosition(), actor->GetPosition()) < 5.0f;
    }
};
}
#endif // !BEHAVIOUR_NOT_AWAY_FROM_HOME_NODE_H