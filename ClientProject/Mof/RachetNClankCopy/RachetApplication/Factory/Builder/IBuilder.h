#ifndef RACHET_IBUILDER_H
#define RACHET_IBUILDER_H


#include <any>


namespace rachet {
class IBuilder {
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    IBuilder() = default;
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~IBuilder() = default;
    /// <summary>
    /// 構築
    /// </summary>
    /// <param name=""></param>
    virtual void Construct(std::any shared_this) = 0;
};
}
#endif // !RACHET_IBUILDER_H