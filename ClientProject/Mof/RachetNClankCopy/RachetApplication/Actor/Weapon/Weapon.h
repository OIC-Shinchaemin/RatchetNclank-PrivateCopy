#ifndef MY_WEAPON_H
#define MY_WEAPON_H


#include "../../Actor.h"

#include <memory>

#include <Mof.h>


namespace my {
class Weapon : public my::Actor {
    using super = my::Actor;
protected:
    std::weak_ptr<Mof::CMeshContainer> _mesh;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Weapon();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Weapon();
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time);
};
}
#endif // !MY_WEAPON_H