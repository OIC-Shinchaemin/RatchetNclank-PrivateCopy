#ifndef RATCHET_CHARACTER_H
#define RATCHET_CHARACTER_H


#include "../../Actor.h"


namespace ratchet {
class Character : public ratchet::Actor {
    using super = ratchet::Actor;
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
#endif // !RATCHET_CHARACTER_H