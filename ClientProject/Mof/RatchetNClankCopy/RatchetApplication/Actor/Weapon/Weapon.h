#ifndef RATCHET_WEAPON_H
#define RATCHET_WEAPON_H


#include "../../Actor.h"


namespace ratchet {
class Weapon : public ratchet::Actor {
    using super = ratchet::Actor;
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
#endif // !RATCHET_WEAPON_H