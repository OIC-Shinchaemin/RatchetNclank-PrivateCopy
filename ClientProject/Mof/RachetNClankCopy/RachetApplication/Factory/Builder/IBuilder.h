#ifndef RATCHET_IBUILDER_H
#define RATCHET_IBUILDER_H


#include <any>


namespace ratchet {
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
#endif // !RATCHET_IBUILDER_H