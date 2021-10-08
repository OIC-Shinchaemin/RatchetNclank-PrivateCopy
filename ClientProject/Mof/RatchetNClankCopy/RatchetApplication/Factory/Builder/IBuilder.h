#ifndef RATCHET_FACTORY_BUILDER_IBUILDER_H
#define RATCHET_FACTORY_BUILDER_IBUILDER_H


#include <any>


namespace ratchet::factory::builder {
class IBuilder {
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    IBuilder() = default;
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~IBuilder() = default;
    /// <summary>
    /// �\�z
    /// </summary>
    /// <param name=""></param>
    virtual void Construct(std::any shared_this) = 0;
};
}
#endif // !RATCHET_FACTORY_BUILDER_IBUILDER_H