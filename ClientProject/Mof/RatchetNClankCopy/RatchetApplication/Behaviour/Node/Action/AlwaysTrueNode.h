#ifndef BEHAVIOUR_ALWAYS_TRUE_NODE_H
#define BEHAVIOUR_ALWAYS_TRUE_NODE_H


#include "../ActionNode.h"


namespace behaviour {
class AlwaysTrueNode : public behaviour::ActionNodeBase {
    using super = behaviour::ActionNodeBase;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    AlwaysTrueNode() :
        super("AlwaysTrueNode") {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~AlwaysTrueNode() = default;
    /// <summary>
    /// �m�[�h�̎��s
    /// </summary>
    /// <param name="actor">���s�A�N�^�[</param>
    /// <returns>true:���s�̐���</returns>
    /// <returns>false:���s�̎��s</returns>
    virtual bool Execute(std::any ptr) override {
        return true;
    }
};
}
#endif // !BEHAVIOUR_ALWAYS_TRUE_NODE_H