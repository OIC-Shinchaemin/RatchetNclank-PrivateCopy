#ifndef BEHAVIOUR_NOT_AWAY_FROM_HOME_NODE_H
#define BEHAVIOUR_NOT_AWAY_FROM_HOME_NODE_H


#include "../ConditionalNode.h"
#include "../../../Actor.h"


namespace behaviour {
class NotAwayFromHomeNode: public behaviour::ConditionalNodeBase {
    using super = behaviour::ConditionalNodeBase;
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
    virtual bool Execute(std::any ptr) override {
        auto actor = std::any_cast<std::shared_ptr<my::Actor>>(ptr);

        return Mof::CVector3Utilities::Distance(actor->GetInitialPosition(), actor->GetPosition()) < 5.0f;
    }
};
}
#endif // !BEHAVIOUR_NOT_AWAY_FROM_HOME_NODE_H