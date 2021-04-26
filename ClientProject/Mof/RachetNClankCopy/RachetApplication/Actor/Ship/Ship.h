#ifndef MY_SHIP_H
#define MY_SHIP_H


#include "../../Actor.h"


namespace my {
class Ship : public my::Actor {
    using super = my::Actor;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Ship();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Ship();
};
}
#endif // !MY_SHIP_H