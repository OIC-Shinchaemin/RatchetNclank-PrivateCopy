#ifndef RACHET_WEAPON_H
#define RACHET_WEAPON_H


#include "../../Actor.h"


namespace rachet {
class Weapon : public rachet::Actor {
    using super = rachet::Actor;
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
#endif // !RACHET_WEAPON_H