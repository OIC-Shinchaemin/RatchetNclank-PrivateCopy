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
    /// コンストラクタ
    /// </summary>
    Mechanical();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Mechanical();
};
}
#endif // !MY_MECHANICAL_H