#ifndef RATCHET_ACTOR_CHARACTER_CHARACTER_H
#define RATCHET_ACTOR_CHARACTER_CHARACTER_H


#include "../Actor.h"


namespace ratchet::actor::character {
class Character : public ratchet::actor::Actor {
    using super = ratchet::actor::Actor;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Character();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Character();
};
}
#endif // !RATCHET_ACTOR_CHARACTER_CHARACTER_H