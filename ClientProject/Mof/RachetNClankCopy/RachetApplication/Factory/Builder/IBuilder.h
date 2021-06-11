#ifndef RACHET_IBUILDER_H
#define RACHET_IBUILDER_H


#include <any>


namespace rachet {
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
#endif // !RACHET_IBUILDER_H