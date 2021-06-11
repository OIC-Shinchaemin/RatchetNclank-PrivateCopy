#ifndef RACHET_WEAPON_H
#define RACHET_WEAPON_H


#include "../../Actor.h"


namespace rachet {
class Weapon : public rachet::Actor {
    using super = rachet::Actor;
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
#endif // !RACHET_WEAPON_H