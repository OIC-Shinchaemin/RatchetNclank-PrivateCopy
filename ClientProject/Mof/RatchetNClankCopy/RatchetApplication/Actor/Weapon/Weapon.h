#ifndef RATCHET_WEAPON_H
#define RATCHET_WEAPON_H


#include "../../Actor.h"


namespace ratchet {
class Weapon : public ratchet::Actor {
    using super = ratchet::Actor;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Weapon();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Weapon();
};
}
#endif // !RATCHET_WEAPON_H