#ifndef RATCHET_ACTOR_WEAPON_WEAPON_H
#define RATCHET_ACTOR_WEAPON_WEAPON_H


#include "../Actor.h"


namespace ratchet {
namespace actor {
namespace weapon {
class Weapon : public ratchet::actor::Actor {
    using super = ratchet::actor::Actor;
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
}
}
#endif // !RATCHET_ACTOR_WEAPON_WEAPON_H