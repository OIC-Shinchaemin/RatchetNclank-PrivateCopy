#ifndef RACHET_OMNI_WRENCH_H
#define RACHET_OMNI_WRENCH_H


#include "Weapon.h"


namespace rachet {
class OmniWrench : public rachet::Weapon {
    using super = rachet::Weapon;
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
    /// ������
    /// </summary>
    /// <param name="param"></param>
    /// <returns></returns>
    virtual bool Initialize(rachet::Actor::Param* param) override;
};
}
#endif // !RACHET_OMNI_WRENCH_H