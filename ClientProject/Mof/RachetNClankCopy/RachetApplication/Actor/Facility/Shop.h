#ifndef MY_SHOP_H
#define MY_SHOP_H


#include "../../Actor.h"


namespace my {
class Shop : public my::Actor {
    using super = my::Actor;
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
#endif // !MY_SHOP_H