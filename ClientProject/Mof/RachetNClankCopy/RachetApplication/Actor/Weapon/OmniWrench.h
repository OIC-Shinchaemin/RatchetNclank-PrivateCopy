#ifndef MY_OMNI_WRENCH_H
#define MY_OMNI_WRENCH_H


#include "Weapon.h"


namespace my {
class OmniWrench : public my::Weapon {
    using super = my::Weapon;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    OmniWrench();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~OmniWrench();
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
};
}
#endif // !MY_OMNI_WRENCH_H