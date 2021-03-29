#ifndef MY_BOMB_GLOVEL_H
#define MY_BOMB_GLOVEL_H


#include "Mechanical.h"


namespace my {
class BombGlove  : public my::Mechanical {
    using super = my::Mechanical;
private:
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    BombGlove();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~BombGlove();
};
}
#endif // !MY_BOMB_GLOVEL_H