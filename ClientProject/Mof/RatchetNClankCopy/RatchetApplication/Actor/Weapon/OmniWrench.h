#ifndef RATCHET_OMNI_WRENCH_H
#define RATCHET_OMNI_WRENCH_H


#include "Weapon.h"


namespace ratchet {
class OmniWrench : public ratchet::Weapon {
    using super = ratchet::Weapon;
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
    virtual bool Initialize(ratchet::Actor::Param* param) override;
};
}
#endif // !RATCHET_OMNI_WRENCH_H