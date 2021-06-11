#ifndef RACHET_SHIP_H
#define RACHET_SHIP_H


#include "../../Actor.h"


namespace rachet {
class Ship : public rachet::Actor {
    using super = rachet::Actor;
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
#endif // !RACHET_SHIP_H