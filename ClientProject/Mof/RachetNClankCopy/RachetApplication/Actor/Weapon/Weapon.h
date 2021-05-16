#ifndef MY_WEAPON_H
#define MY_WEAPON_H


#include "../../Actor.h"


namespace my {
class Weapon : public my::Actor {
    using super = my::Actor;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Weapon();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Weapon();
};
}
#endif // !MY_WEAPON_H