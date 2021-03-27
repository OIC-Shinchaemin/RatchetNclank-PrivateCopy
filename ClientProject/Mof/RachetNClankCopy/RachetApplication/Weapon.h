#ifndef MY_WEAPON_H
#define MY_WEAPON_H


#include "Actor.h"
#include "ResourceLocator.h"

#include <memory>

#include <Mof.h>


namespace my {
class Weapon : public my::Actor , public my::ResourceLocator{
    using super = my::Actor;
private:
    //! ���b�V��
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
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void);
};
}
#endif // !MY_WEAPON_H