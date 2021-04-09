#ifndef MY_IBUILDER_H
#define MY_IBUILDER_H


#include <any>


namespace my {
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
#endif // !MY_IBUILDER_H