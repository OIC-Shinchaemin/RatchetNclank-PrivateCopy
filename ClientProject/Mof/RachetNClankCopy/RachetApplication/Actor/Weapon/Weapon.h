#ifndef MY_WEAPON_H
#define MY_WEAPON_H


#include "../../Actor.h"


namespace my {
class Weapon : public my::Actor {
    using super = my::Actor;
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
#endif // !MY_WEAPON_H