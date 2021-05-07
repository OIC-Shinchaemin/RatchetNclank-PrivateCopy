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
    /// �R���X�g���N�^
    /// </summary>
    Weapon();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Weapon();
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time);
};
}
#endif // !MY_WEAPON_H