#ifndef BEHAVIOUR_TARGET_RECOGNITION_NODE_H
#define BEHAVIOUR_TARGET_RECOGNITION_NODE_H


#include "../ConditionalNode.h"

#include "../../../Actor.h"
#include "../../../Component/Enemy/EnemyComponent.h"


namespace behaviour {
class TargetRecognitionNode : public behaviour::ConditionalNodeBase {
    using super = behaviour::ConditionalNodeBase;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    TargetRecognitionNode() :
        super("TargetRecognition") {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~TargetRecognitionNode() = default;
    /// <summary>
    /// �m�[�h�̎��s����
    /// </summary>
    /// <param name="actor">���s�A�N�^�[</param>
    /// <returns>Succeeded:���s�̐���</returns>
    /// <returns>Failed:���s�̎��s</returns>
    virtual bool Execute(std::any ptr) override {
        auto actor =  std::dynamic_pointer_cast<my::Enemy>(std::any_cast<std::shared_ptr<my::Actor>>(ptr));
        auto target = actor->GetComponent<my::EnemyComponent>()->GetTarget();
        return !target.expired();
    }
};
}
#endif // !BEHAVIOUR_TARGET_RECOGNITION_NODE_H