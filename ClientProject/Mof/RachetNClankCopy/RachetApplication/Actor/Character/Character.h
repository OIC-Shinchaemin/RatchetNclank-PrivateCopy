#ifndef MY_CHARACTER_H
#define MY_CHARACTER_H


#include "../../Actor.h"


namespace my {
class Character : public my::Actor {
    using super = my::Actor;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Character();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Character();
};
}
#endif // !MY_CHARACTER_H