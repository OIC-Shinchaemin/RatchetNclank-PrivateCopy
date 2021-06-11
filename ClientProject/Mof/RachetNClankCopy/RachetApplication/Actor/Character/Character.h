#ifndef RACHET_CHARACTER_H
#define RACHET_CHARACTER_H


#include "../../Actor.h"


namespace rachet {
class Character : public rachet::Actor {
    using super = rachet::Actor;
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
#endif // !RACHET_CHARACTER_H