#ifndef RATCHET_BEHAVIOUR_ALWAYS_TRUE_NODE_H
#define RATCHET_BEHAVIOUR_ALWAYS_TRUE_NODE_H


#include "../ActionNode.h"


namespace ratchet {  namespace behaviour {
class AlwaysTrueNode : public ratchet::behaviour::ActionNodeBase {
    using super = ratchet::behaviour::ActionNodeBase;
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
}
#endif // !RATCHET_BEHAVIOUR_ALWAYS_TRUE_NODE_H