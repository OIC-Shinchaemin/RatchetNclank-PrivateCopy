#ifndef RACHET_SHOP_H
#define RACHET_SHOP_H


#include "../../Actor.h"


namespace rachet {
class Shop : public rachet::Actor {
    using super = rachet::Actor;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Shop();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Shop();
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
};
}
#endif // !RACHET_SHOP_H