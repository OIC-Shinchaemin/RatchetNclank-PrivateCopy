#ifndef MY_MECHANICAL_H
#define MY_MECHANICAL_H


#include "Weapon.h"


namespace my {
class Mechanical : public my::Weapon {
    using super = my::Weapon;
protected:
    std::size_t _bullet_size;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Mechanical();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Mechanical();
};
}
#endif // !MY_MECHANICAL_H