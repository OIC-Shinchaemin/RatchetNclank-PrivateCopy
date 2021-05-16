#ifndef MY_IBUILDER_H
#define MY_IBUILDER_H


#include <any>


namespace my {
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
#endif // !MY_IBUILDER_H