#ifndef MY_BOMB_GLOVEL_H
#define MY_BOMB_GLOVEL_H


#include "Mechanical.h"


namespace my {
class BombGlove  : public my::Mechanical {
    using super = my::Mechanical;
private:
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    BombGlove();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~BombGlove();
};
}
#endif // !MY_BOMB_GLOVEL_H