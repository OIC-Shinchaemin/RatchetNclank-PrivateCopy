#ifndef MY_SHIP_H
#define MY_SHIP_H


#include "../../Actor.h"


namespace my {
class Ship : public my::Actor {
    using super = my::Actor;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Ship();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Ship();
};
}
#endif // !MY_SHIP_H