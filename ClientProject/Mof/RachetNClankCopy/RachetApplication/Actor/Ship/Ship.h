#ifndef MY_SHIP_H
#define MY_SHIP_H


#include "../../Actor.h"


namespace my {
class Ship : public my::Actor {
    using super = my::Actor;
public:
    enum class MotionType {
        Default,
        V4,
        CountMax,
    };
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Ship();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Ship();
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name="builder"></param>
    virtual void Construct(const std::shared_ptr<class IBuilder>& builder) override;
};
}
#endif // !MY_SHIP_H